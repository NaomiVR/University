// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class CELESTIAL_CHAOS_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawner();

	UPROPERTY(EditDefaultsOnly, Category="Spawning")
	TArray<TSubclassOf<ACharacter>> EnemyClasses;

	UPROPERTY(EditDefaultsOnly, Category="Spawning")
	float SpawnRate;

	UPROPERTY(EditDefaultsOnly, Category="Spawning")
	int32 SpawnCount;

	UPROPERTY(EditDefaultsOnly, Category="Spawning")
	int32 BaseSpawnLimit;

	UPROPERTY(EditDefaultsOnly, Category="Spawning")
	int32 EnemiesToSpawnPerLoop;

	UPROPERTY(EditDefaultsOnly, Category="Spawning")
	float GrowthRate;

	UFUNCTION()
	void SpawnRandomEnemy();

	UFUNCTION()
	void IncreaseSpawnLimit();

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle SpawnTimerHandle;
	FTimerDelegate SpawnTimerDelegate;
	FTimerHandle SpawnLimitTimerHandle;
	FTimerDelegate SpawnLimitTimerDelegate;
	int32 MaxEntityLimit;
	float TimeElapsed;
};
