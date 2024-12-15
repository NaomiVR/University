#include "Randomizer.h"
#include "VarContainer.h"

FRandomizer::FRandomizer()
{
	RandomStream.Initialize(FMath::Rand());
}

void FRandomizer::RandomiseVariables()
{
	RandomTW = RandomStream.FRandRange(1, 255);
	RandomTL = RandomStream.FRandRange(1, 255);

	RandomSL = RandomStream.FRandRange(0, 1);
	RandomMiSHR = RandomStream.FRandRange(0, 255);
	RandomMaSHR = RandomStream.FRandRange(0, 255);
	RandomHFL = RandomStream.FRandRange(-1, 1);

	RandomO = RandomStream.FRandRange(1, 5);
	RandomSF = RandomStream.FRandRange(0, 1);
	RandomHM = RandomStream.FRandRange(1, 100);
	RandomP = RandomStream.FRandRange(0, 1);

	SetRandomisedVariables();
}

void FRandomizer::SetRandomisedVariables()
{
	FVarContainer* VarContainer = FVarContainer::GetInstance();
	
	VarContainer->SetTerrainWidth(RandomTW);
	VarContainer->SetTerrainLength(RandomTL);

	VarContainer->SetSeaLevel(RandomSL);
	VarContainer->SetMinStartRiverHeight(RandomMiSHR);
	VarContainer->SetMaxStartRiverHeight(RandomMaSHR);
	VarContainer->SetHardFloorHeight(RandomHFL);

	VarContainer->SetOctaves(RandomO);
	VarContainer->SetScaleFactor(RandomSF);
	VarContainer->SetHeightMultiplier(RandomHM);
	VarContainer->SetPersistence(RandomP);

	// UE_LOG(LogTemp, Log, TEXT("RandomTW: %d, RandomTL: %d, RandomSL: %d, RandomMiSHR: %d, RandomMaSHR: %d, RandomHFL: %f, RandomO: %d, RandomSF: %f, RandomHM: %d, RandomP: %f"),
		// RandomTW, RandomTL, RandomSL, RandomMiSHR, RandomMaSHR, RandomHFL, RandomO, RandomSF, RandomHM, RandomP);
}

