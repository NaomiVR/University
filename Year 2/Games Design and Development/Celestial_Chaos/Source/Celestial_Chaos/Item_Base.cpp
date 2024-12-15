// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Base.h"
#include "CharacterInventoryComponent.h"
#include "GameFramework/Character.h"


AItem_Base::AItem_Base()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AItem_Base::BeginPlay()
{
	Super::BeginPlay();
}


void AItem_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem_Base::OnPickedUp(ACharacter* Character)
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

