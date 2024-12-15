// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPTestSpawner.h"
#include "GameFramework/Character.h"

// Sets default values
ACPPTestSpawner::ACPPTestSpawner()
{
 	SpawnCount = 0;
	BaseSpawnLimit = 10;
	MaxEntityLimit = 1000;
	EnemiesToSpawnPerLoop = 5;
	TimeElapsed = 0.0f;
	GrowthRate = 0.1f;
}


void ACPPTestSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnTimerDelegate.BindUFunction(this, FName("SpawnRandomEnemy"));
	SpawnLimitTimerDelegate.BindUFunction(this, FName("IncreaseSpawnLimit"));

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, SpawnTimerDelegate, SpawnRate, true);
	GetWorldTimerManager().SetTimer(SpawnLimitTimerHandle, SpawnLimitTimerDelegate, 15.0f, true);
}


void ACPPTestSpawner::SpawnRandomEnemy()
{
	if (SpawnCount < BaseSpawnLimit)
	{
		for (int32 i = 0; i < EnemiesToSpawnPerLoop; ++i)
		{
			int32 RandomIndex = FMath::RandRange(0, EnemyClasses.Num() - 1);
			TSubclassOf<ACharacter> RandomEnemyClass = EnemyClasses[RandomIndex];

			FVector SpawnLocation = GetActorLocation();
			FRotator SpawnRotation = GetActorRotation();
            
			ACharacter* SpawnedEnemy = GetWorld()->SpawnActor<ACharacter>(RandomEnemyClass, SpawnLocation, SpawnRotation);
			if (SpawnedEnemy != nullptr)
			{
				++SpawnCount;
			}
		}
	}
}


void ACPPTestSpawner::IncreaseSpawnLimit()
{
	TimeElapsed += 30.0f;
	BaseSpawnLimit += FMath::CeilToInt(GrowthRate * TimeElapsed);

	EnemiesToSpawnPerLoop += 1;

	if (BaseSpawnLimit > MaxEntityLimit)
	{
		BaseSpawnLimit = MaxEntityLimit;
	}
}
