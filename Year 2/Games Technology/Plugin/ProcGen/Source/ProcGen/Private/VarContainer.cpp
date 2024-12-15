#include "VarContainer.h"

FVarContainer* FVarContainer::InstancePtr = nullptr;

FVarContainer* FVarContainer::GetInstance()
{
	if (InstancePtr == nullptr)
		{
			InstancePtr = new FVarContainer();
		}
	return InstancePtr;
}

void FVarContainer::SetTerrainWidth(uint8 var)
{
	TerrainWidth = var;
}

void FVarContainer::SetTerrainLength(uint8 var)
{
	TerrainLength = var;
}

void FVarContainer::SetSeaLevel(float var)
{
	SeaLevel = var;
}

void FVarContainer::SetMinStartRiverHeight(uint8 var)
{
	MinStartRiverHeight = var;
}

void FVarContainer::SetMaxStartRiverHeight(uint8 var)
{
	MaxStartRiverHeight = var;
}

void FVarContainer::SetHardFloorHeight(float var)
{
	HardFloorHeight = var;
}

void FVarContainer::SetOctaves(uint8 var)
{
	Octaves = var;
}

void FVarContainer::SetScaleFactor(float var)
{
	ScaleFactor = var;
}

void FVarContainer::SetHeightMultiplier(uint8 var)
{
	HeightMultiplier = var;
}

void FVarContainer::SetPersistence(float var)
{
	Persistence = var;
}

//----------------------------------------------------------------

uint8 FVarContainer::GetTerrainWidth() const
{
	return TerrainWidth;
}

uint8 FVarContainer::GetTerrainLength() const
{
	return TerrainLength;
}

float FVarContainer::GetSeaLevel() const
{
	return SeaLevel;
}

uint8 FVarContainer::GetMinStartRiverHeight() const
{
	return MinStartRiverHeight;
}

uint8 FVarContainer::GetMaxStartRiverHeight() const
{
	return MaxStartRiverHeight;
}

float FVarContainer::GetHardFloorHeight() const
{
	return HardFloorHeight;
}

uint8 FVarContainer::GetOctaves() const
{
	return Octaves;
}

float FVarContainer::GetScaleFactor() const
{
	return ScaleFactor;
}

uint8 FVarContainer::GetHeightMultiplier() const
{
	return HeightMultiplier;
}

float FVarContainer::GetPersistence() const
{
	return Persistence;
}


void FVarContainer::SetTerrainMeshInstance(ATerrainMesh* var)
{
	TerrainMeshInstance = var;
}

ATerrainMesh* FVarContainer::GetTerrainMeshInstance()
{
	return TerrainMeshInstance;
}

