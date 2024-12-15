// Fill out your copyright notice in the Description page of Project Settings.


#include "CelestialCore.h"

#include "CharacterStatsComponent.h"
#include "GameFramework/Character.h"


ACelestialCore::ACelestialCore()
{
	UStaticMeshComponent* CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	RootComponent = CubeMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Game/Assets/3D/Shape_Cube'"));
	if (CubeMeshAsset.Succeeded())
	{
		CubeMesh->SetStaticMesh(CubeMeshAsset.Object);
	}
}



void ACelestialCore::OnPickedUp(ACharacter* Character)
{
	Super::OnPickedUp(Character);

	if (Character)
	{
		UCharacterStatsComponent* StatComponent = Character->FindComponentByClass<UCharacterStatsComponent>();
		
		if (StatComponent)
		{
			StatComponent->IncreaseMaxHealth(100);
		}
	}

	Destroy();
}

