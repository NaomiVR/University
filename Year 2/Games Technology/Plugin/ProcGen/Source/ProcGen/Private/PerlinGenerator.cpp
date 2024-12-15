#include "PerlinGenerator.h"
#include "GetTerrainColour.h"
#include "TerrainMesh.h"
#include "VarContainer.h"


FPerlinGenerator::FPerlinGenerator(ATerrainMesh* var)
{
	HardFloorHeight = FVarContainer::GetInstance()->GetHardFloorHeight();
	Octaves = FVarContainer::GetInstance()->GetOctaves();
	ScaleFactor = FVarContainer::GetInstance()->GetScaleFactor();
	HeightMultiplier = FVarContainer::GetInstance()->GetHeightMultiplier();
	Persistence = FVarContainer::GetInstance()->GetPersistence();
	TerrainMesh = var;
}


void FPerlinGenerator::Generator()
{
	FVarContainer* VarContainer = FVarContainer::GetInstance();
	FGetTerrainColour ColourPicker = FGetTerrainColour();

	for (float x = 0; x < VarContainer->GetTerrainWidth(); x++)
	{
		float XCoord = x * ScaleFactor; // Assume between 0 and 1 (darren used 0.008)
		
		for (float y = 0; y < VarContainer->GetTerrainLength(); y++)
		{
			float YCoord = y * ScaleFactor;

			float NoiseValue = 0.0f;
			float Amplitude = 1.0f;
			float Frequency = 1.0f;

			for (int32 i = 0; i < Octaves; i++)
			{
				NoiseValue += FMath::PerlinNoise2D(FVector2D(XCoord * Frequency, YCoord * Frequency)) * Amplitude;

				Frequency *= 2.0f;
				Amplitude *= Persistence; // Persistence normally between 0 and 1
			}

			if (TerrainMesh) {
				if (NoiseValue > HardFloorHeight)
					{
						FVector TerrainPoint(x, y, NoiseValue * HeightMultiplier);
						
						TerrainMesh->AddPoint(TerrainPoint);
						TerrainMesh->AddVertexColour(ColourPicker.GetTerrainColour(NoiseValue, false));
						// TerrainMesh->AddVertexColour(FColor(1.f, 1.f, 1.f, 255));
					}
					else
					{
						FVector TerrainPoint(x, y, HardFloorHeight);
						
						TerrainMesh->AddPoint(TerrainPoint);
						TerrainMesh->AddVertexColour(ColourPicker.GetTerrainColour(NoiseValue, false));
						// TerrainMesh->AddVertexColour(FColor(1.f, 1.f, 1.f, 255));
					}
			}
		}
	}
	
	TerrainMesh->FormTriangles();
	TerrainMesh->UpdateMesh();
}
