// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Components/ActorComponent.h"
#include "CharacterInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CELESTIAL_CHAOS_API UCharacterInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCharacterInventoryComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	TArray<TSubclassOf<AItemBase>> Inventory;

protected:
	virtual void BeginPlay() override;

public:
	void AddItemToInventory(TSubclassOf<AItemBase> Item);
};
