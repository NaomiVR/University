#pragma once
#include "TerrainMesh.h"

class FVarContainer
{
public:
	static FVarContainer *GetInstance();
	
	void SetTerrainWidth(uint8 var);
	void SetTerrainLength(uint8 var);
	void SetSeaLevel(float var);
	void SetMinStartRiverHeight(uint8 var);
	void SetMaxStartRiverHeight(uint8 var);
	void SetHardFloorHeight(float var);
	
	void SetOctaves(uint8 var);
	void SetScaleFactor(float var);
	void SetHeightMultiplier(uint8 var);
	void SetPersistence(float var);

	uint8 GetTerrainWidth() const;
	uint8 GetTerrainLength() const;
	float GetSeaLevel() const;
	uint8 GetMinStartRiverHeight() const;
	uint8 GetMaxStartRiverHeight() const;
	float GetHardFloorHeight() const;
	
	uint8 GetOctaves() const;
	float GetScaleFactor() const;
	uint8 GetHeightMultiplier() const;
	float GetPersistence() const;

	
	void SetTerrainMeshInstance(ATerrainMesh* var);
	ATerrainMesh* GetTerrainMeshInstance();

private:
	FVarContainer() {}
	FVarContainer(const FVarContainer&) = delete;
	FVarContainer& operator=(const FVarContainer&) = delete;

	static FVarContainer* InstancePtr;

	//Terrain actor info
	ATerrainMesh* TerrainMeshInstance = nullptr;
	
	//Globally required variables
	uint8 TerrainWidth = 0;
	uint8 TerrainLength = 0;
	int8 SeaLevel = 0;
	uint8 MinStartRiverHeight = 0;
	uint8 MaxStartRiverHeight = 0;
	float HardFloorHeight = 0;

	//Perlin noise variables
	uint8 Octaves = 0;
	float ScaleFactor = 0;
	uint8 HeightMultiplier = 0;
	float Persistence = 0;

	//File save data
};
