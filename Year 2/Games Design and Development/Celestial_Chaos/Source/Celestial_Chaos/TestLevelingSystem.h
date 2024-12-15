// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TestLevelingSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CELESTIAL_CHAOS_API UTestLevelingSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTestLevelingSystem();

	UPROPERTY(EditAnywhere, Category="Leveling")
	float Level;

	UPROPERTY(EditAnywhere, Category="Leveling")
	int32 Experience;

	UFUNCTION()
	int32 ExperienceIncrement();

	UFUNCTION()
	int32 LevelUp();

protected:
	int32 NewExperienceLimit;

public:	

		
};
