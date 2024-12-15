/*
// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDropComponent.h"
#include "GameFramework/Character.h"


UItemDropComponent::UItemDropComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UItemDropComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (Owner)
	{
		Owner->OnDestroyed.AddDynamic(this, &UItemDropComponent::OnCharacterDeath);
	}
}

void UItemDropComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UItemDropComponent::OnCharacterDeath(ACharacter* DestroyedActor)
{
	if (DropItems.Num() > 0)
	{
		int32 ItemIndex = FMath::RandRange(0, DropItems.Num() - 1);
		TSubclassOf<AItemBase> ItemToDrop = DropItems[ItemIndex];

		ACharacter* OwnerCharacter = Cast<ACharacter>(DestroyedActor);
		if (OwnerCharacter)
		{
			FVector SpawnLocation = OwnerCharacter->GetActorLocation();
			FRotator SpawnRotation = OwnerCharacter->GetActorRotation();

			AItemBase* DroppedItem = GetWorld()->SpawnActor<AItemBase>(ItemToDrop, SpawnLocation, SpawnRotation);
		}
	}
}
*/


