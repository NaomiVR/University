// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStatsComponent.h"
#include "Components/ActorComponent.h"
#include "CharacterLevelingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CELESTIAL_CHAOS_API UCharacterLevelingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterLevelingComponent();

	UPROPERTY(EditDefaultsOnly, Category="Leveling")
	UCharacterStatsComponent* StatsComponent;

	UFUNCTION()
	void HandleXPChanged(float Var);

	UFUNCTION()
	void LevelUp();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float XpToNextLevel;
	float CurrLevel;
};
