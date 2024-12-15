// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterInventoryComponent.h"


UCharacterInventoryComponent::UCharacterInventoryComponent()
{
}


void UCharacterInventoryComponent::BeginPlay()
{
}


void UCharacterInventoryComponent::AddItemToInventory(TSubclassOf<AItemBase> Item)
{
	Inventory.Add(Item);
}
