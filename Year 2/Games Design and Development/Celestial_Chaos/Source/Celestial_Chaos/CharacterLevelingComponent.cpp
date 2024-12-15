// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterLevelingComponent.h"
#include "CharacterStatsComponent.h"

UCharacterLevelingComponent::UCharacterLevelingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterLevelingComponent::BeginPlay()
{
	Super::BeginPlay();

	StatsComponent = GetOwner()->FindComponentByClass<UCharacterStatsComponent>();

	if (StatsComponent)
	{
		StatsComponent->OnXpChanged.AddDynamic(this, &UCharacterLevelingComponent::HandleXPChanged);
	}
}

void UCharacterLevelingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrLevel = StatsComponent->Level;
}


void UCharacterLevelingComponent::HandleXPChanged(float NewXp)
{
	if (NewXp >= XpToNextLevel)
	{
		LevelUp();
	}
}


void UCharacterLevelingComponent::LevelUp()
{	
	StatsComponent->Level++;
	CurrLevel = StatsComponent->Level;
	XpToNextLevel = 500 * (CurrLevel * CurrLevel) - (500 * CurrLevel);

	StatsComponent->MaxHealth += 20 * CurrLevel;
	StatsComponent->AdditionalSkillDamage += 5 * CurrLevel;
	StatsComponent->MovementSpeed += 0.1f * CurrLevel;
}
