#include "TerrainMesh.h"
#include "MaterialDomain.h"
#include "ProceduralMeshComponent.h"
#include "VarContainer.h"

ATerrainMesh::ATerrainMesh()
{
	World = GetWorld();
	FVector Location = FVector(0.0f, 0.0f, 0.0f);
	FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);

	if (World)
	{
		PrimaryActorTick.bCanEverTick = false;
		ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
		SetRootComponent(ProceduralMesh);
		ProceduralMesh->bUseAsyncCooking = true;

		if (ProceduralMesh)
		{
			// UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr,
					// TEXT("/Script/Engine.Material'/Game/Materials/VertexShader.VertexShader'"));
			// if (Material)
				// {
					// ProceduralMesh->SetMaterial(0, Material);
				// }

			UMaterial* Material = UMaterial::GetDefaultMaterial(MD_Surface);
			if (Material)
			{
				ProceduralMesh->SetMaterial(0, Material);
			}
		}
	}
}

ATerrainMesh::~ATerrainMesh()
{
	// Causing EXCEPTION_STACK_OVERFLOW error upon editor close due to recursive deleting, it's
	// deleting its own pointer calling the destructor again and again
	/*delete FVarContainer::GetInstance()->GetTerrainMeshInstance();
	FVarContainer::GetInstance()->SetTerrainMeshInstance(nullptr);*/
}

void ATerrainMesh::AddPoint(FVector Point)
{
	Vertices.Add(Point);
}

void ATerrainMesh::AddVertexColour(FLinearColor Colour)
{
	Colours.Add(Colour);
}

void ATerrainMesh::FormTriangles()
{
	UE_LOG(LogTemp, Log, TEXT("Forming mesh triangles"));
	FVarContainer* VarContainer = FVarContainer::GetInstance();
	for(int16 i = 0; i < VarContainer->GetTerrainWidth(); i++)
	{
		for(int16 j = 0; j < VarContainer->GetTerrainLength(); j++)
		{
			Triangles.Add(i*VarContainer->GetTerrainWidth() + 1 + j);
			Triangles.Add(i*VarContainer->GetTerrainWidth() + 1 + j + 1);
			Triangles.Add(i*VarContainer->GetTerrainWidth() + 1 + j + VarContainer->GetTerrainWidth() + 1);
			
			Triangles.Add(i*VarContainer->GetTerrainWidth() + 1 + j + 1);
			Triangles.Add(i*VarContainer->GetTerrainWidth() + 1 + j + VarContainer->GetTerrainWidth() + 1 + 1);
			Triangles.Add(i*VarContainer->GetTerrainWidth() + 1 + j + VarContainer->GetTerrainWidth() + 1);
		}
	}
}

void ATerrainMesh::UpdateMesh() const
{
	UE_LOG(LogTemp, Log, TEXT("Updating the mesh"))
	ProceduralMesh->ClearAllMeshSections();
	ProceduralMesh->CreateMeshSection_LinearColor(
		0,
		Vertices,
		Triangles,
		TArray<FVector>(),
		TArray<FVector2D>(),
		Colours,
		TArray<FProcMeshTangent>(),
		true);
}

void ATerrainMesh::ClearMesh() const
{
	// Vertices.Empty();
	// Triangles.Empty();
	// Colours.Empty();

	if (ProceduralMesh)
	{
		ProceduralMesh->ClearAllMeshSections();
	}
}
