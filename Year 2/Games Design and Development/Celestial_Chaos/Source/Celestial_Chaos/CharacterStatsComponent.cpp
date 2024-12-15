// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatsComponent.h"

UCharacterStatsComponent::UCharacterStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PassiveRegen();
}


void UCharacterStatsComponent::PassiveRegen()
{
	Health += PassiveHealthRegeneration;
}


void UCharacterStatsComponent::AddXp(float Amount)
{
	Experience += Amount;
	OnXpChanged.Broadcast(Experience);
}


void UCharacterStatsComponent::IncreaseMaxHealth(float Amount)
{
	MaxHealth += Amount;
}

