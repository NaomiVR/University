// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"


UCLASS()
class CELESTIAL_CHAOS_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:
	AItemBase();
	
	UFUNCTION(BlueprintCallable)
	virtual void OnPickedUp(ACharacter* Character);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
