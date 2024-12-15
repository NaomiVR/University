// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSecondarySkill.h"
#include "GameFramework/Character.h"

UCharacterSecondarySkill::UCharacterSecondarySkill()
{
	PrimaryComponentTick.bCanEverTick = true;
	TimeSinceLastUse = 0.0f;
	Cooldown = 20.0f;
	MaxRange = 500.0f;
	SkillDamage = 150.0f;
	ActivationTime = 0.9f;
}

void UCharacterSecondarySkill::BeginPlay()
{
	Super::BeginPlay();
}

void UCharacterSecondarySkill::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceLastUse += DeltaTime;
}

void UCharacterSecondarySkill::UseSkill()
{
	if (TimeSinceLastUse >= Cooldown)
	{
		ACharacter* Owner = Cast<ACharacter>(GetOwner());
		if (!Owner) return;

		TimeSinceLastUse = 0.0f;
		
		FVector PlayerLocation = Owner->GetActorLocation();
		FVector PlayerForwardVector = Owner->GetActorForwardVector();

		HitCharacters.Empty();

		FVector EndPoint = PlayerLocation + (PlayerForwardVector * MaxRange);

		TArray<FHitResult> HitResults;
		FCollisionShape CollisionShape;
		CollisionShape.SetSphere(MaxRange);

		bool bHit = GetWorld()->SweepMultiByChannel(HitResults, PlayerLocation, EndPoint, FQuat::Identity, ECC_Visibility, CollisionShape);

		if (bHit)
		{
			for (auto& HitResult : HitResults)
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
			}
		}
	}
}
