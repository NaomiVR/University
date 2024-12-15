// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "CharacterInventoryComponent.h"
#include "GameFramework/Character.h"


AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}


void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemBase::OnPickedUp(ACharacter* Character)
{
	if (Character)
	{
		UCharacterInventoryComponent* InventoryComponent = Character->FindComponentByClass<UCharacterInventoryComponent>();

		if (InventoryComponent)
		{
			InventoryComponent->AddItemToInventory(this->GetClass());
		}

		Destroy();
	}
}
