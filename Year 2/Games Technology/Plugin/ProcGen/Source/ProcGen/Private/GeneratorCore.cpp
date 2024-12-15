#include "GeneratorCore.h"
#include "PerlinGenerator.h"
#include "ProcGen.h"
#include "VarContainer.h"


void FGeneratorCore::GenerateMesh()
{
	UE_LOG(LogTemp, Log, TEXT("Generate Mesh called succesfully"))
	FPerlinGenerator NewGenerator = FPerlinGenerator(FVarContainer::GetInstance()->GetTerrainMeshInstance());
	NewGenerator.Generator();
}







