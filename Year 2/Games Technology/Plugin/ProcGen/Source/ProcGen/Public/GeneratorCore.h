#pragma once

class FGeneratorCore
{
public:
	FGeneratorCore() {};

	void GenerateHeightMap();
	void GenerateRivers();

	void GenerateMesh();
	void ApplyWindingOrder();
	void ApplyConstrainedDelauney();

	void DrawMesh();
	void StoreMeshData();
};
