#include "GetTerrainColour.h"
#include "VarContainer.h"


FLinearColor FGetTerrainColour::GetTerrainColour(float Height, bool IsRiver)
{
	FLinearColor Colour;
	float SeaLevel = FVarContainer::GetInstance()->GetSeaLevel();

	if (IsRiver)
	{
		// River
		Colour = FColor::Blue;
	}
	else if (Height < SeaLevel)
	{
		// Water
		Colour = FColor::Blue;
	}
	else if (Height < SeaLevel + 0.1f)
	{
		// Beach
		Colour = FColor::Yellow;
	}
	else if (Height < SeaLevel + 0.3f)
	{
		// Grassland
		Colour = FColor::Green;
	}
	else if (Height < SeaLevel + 0.5f)
	{
		// Mountain
		Colour = FColor(80, 80, 90, 255);
	}
	else
	{
		// Snow
		Colour = FColor::White;
	}

	return Colour;
}

