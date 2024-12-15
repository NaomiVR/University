// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item_Base.generated.h"


UCLASS()
class CELESTIAL_CHAOS_API AItem_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem_Base();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void OnPickedUp(ACharacter* Character);
};
