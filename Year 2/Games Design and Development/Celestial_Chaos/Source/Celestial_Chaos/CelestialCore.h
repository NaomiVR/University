// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "CelestialCore.generated.h"


UCLASS()
class CELESTIAL_CHAOS_API ACelestialCore : public AItemBase
{
	GENERATED_BODY()

public:
	ACelestialCore();
	virtual void OnPickedUp(ACharacter* Character) override;
};
