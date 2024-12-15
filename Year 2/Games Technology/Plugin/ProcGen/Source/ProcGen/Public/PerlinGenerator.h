#pragma once
#include "TerrainMesh.h"

class FPerlinGenerator
{
public:	
	FPerlinGenerator(ATerrainMesh* var);

	void Generator();

private:
	uint8 HardFloorHeight;
	uint8 Octaves;
	float ScaleFactor;
	uint8 HeightMultiplier;
	float Persistence;
	ATerrainMesh* TerrainMesh;
};
