// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterUltimateSkill.h"
#include "CharacterPrimarySkill.h"
#include "CharacterSecondarySkill.h"
#include "GameFramework/Character.h"
#include "CharacterStatsComponent.h"

UCharacterUltimateSkill::UCharacterUltimateSkill()
{
	PrimaryComponentTick.bCanEverTick = true;
	TimeSinceLastUse = 0.0f;
	Cooldown = 90.0f;
	ActivationTime = 1.5f;
}

void UCharacterUltimateSkill::BeginPlay()
{
	Super::BeginPlay();
}

void UCharacterUltimateSkill::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceLastUse += DeltaTime;
}

void UCharacterUltimateSkill::UseSkill()
{
	if (TimeSinceLastUse >= Cooldown)
	{
		ACharacter* Owner = Cast<ACharacter>(GetOwner());
		if (!Owner) return;

		TimeSinceLastUse = 0.0f;

		UCharacterStatsComponent* StatsComponent = Owner->FindComponentByClass<UCharacterStatsComponent>();
		if (!StatsComponent) return;
		
		StatsComponent->Defence *= 1.5f;
		StatsComponent->MovementSpeed *= 1.1f;

		UCharacterPrimarySkill* PrimarySkillComponent = Owner->FindComponentByClass<UCharacterPrimarySkill>();
		UCharacterSecondarySkill* SecondarySkillComponent = Owner->FindComponentByClass<UCharacterSecondarySkill>();

		if (PrimarySkillComponent)
		{
			PrimarySkillComponent->SkillDamage *= 1.5f;
		}
		if (SecondarySkillComponent)
		{
			SecondarySkillComponent->SkillDamage *= 1.5f;
		}
	}
}

