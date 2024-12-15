// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPrimarySkill.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

UCharacterPrimarySkill::UCharacterPrimarySkill()
{
	PrimaryComponentTick.bCanEverTick = true;
	TimeSinceLastUse = 0.0f;
	Cooldown = 0.1f;
	ConeAngle = 45.0f;
	MaxRange = 500.0f;
	StepSize = 5.0f;
	SkillDamage = 55.0f;
}

void UCharacterPrimarySkill::BeginPlay()
{
	Super::BeginPlay();
}

void UCharacterPrimarySkill::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceLastUse += DeltaTime;
}

void UCharacterPrimarySkill::UseSkill()
{
	if (TimeSinceLastUse >= Cooldown)
	{
		ACharacter* Owner = Cast<ACharacter>(GetOwner());
		if (!Owner) return;

		TimeSinceLastUse = 0.0f;
		
		FVector PlayerLocation = Owner->GetActorLocation();
		FVector PlayerForwardVector = Owner->GetActorForwardVector();

		HitCharacters.Empty();

		for (float Angle = -ConeAngle; Angle <= ConeAngle; Angle += StepSize)
		{
			FVector Direction = UKismetMathLibrary::RotateAngleAxis(PlayerForwardVector, Angle, FVector::UpVector);
			FVector EndPoint = PlayerLocation + (Direction * MaxRange);

			FHitResult HitResult;
			bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, PlayerLocation, EndPoint, ECC_Visibility);

			if (bHit)
			{
				if (ACharacter* HitCharacter = Cast<ACharacter>(HitResult.GetActor()))
				{
					HitCharacters.Add(TWeakObjectPtr<ACharacter>(HitCharacter));
				}
			}
		}

		for (TWeakObjectPtr<ACharacter> WeakCharacter : HitCharacters)
		{
			if (ACharacter* Character = WeakCharacter.Get())
			{
				UFunction* TakeDamage = Character->GetClass()->FindFunctionByName(TEXT("TakeDamage"));

				if (TakeDamage)
				{
					struct FTakeDamageParams
					{
						float Damage;
					};

					FTakeDamageParams Params;
					Params.Damage = SkillDamage;

					Character->ProcessEvent(TakeDamage, &Params);
				}

				FVector Direction = Character->GetActorLocation() - Owner->GetActorLocation();
				Direction.Normalize();

				float ForceMagnitude = 1000.0f;
				Character->GetCharacterMovement()->AddForce(Direction * ForceMagnitude);
			}
		}
	}
}
