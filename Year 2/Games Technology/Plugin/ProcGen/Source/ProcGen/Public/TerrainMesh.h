#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "TerrainMesh.generated.h"

UCLASS()
class ATerrainMesh : public AActor
{
	GENERATED_BODY()

public:
	ATerrainMesh();
	virtual ~ATerrainMesh() override;

	void AddPoint(FVector Point);
	void AddVertexColour(FLinearColor Colour);
	void FormTriangles();
	void UpdateMesh() const;
	void ClearMesh() const;

	UWorld* World;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FLinearColor> Colours;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UProceduralMeshComponent* ProceduralMesh;
};
