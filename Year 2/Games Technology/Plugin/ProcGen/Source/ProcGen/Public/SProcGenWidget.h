#pragma once


class SProcGenWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SProcGenWidget)
	{ }
	SLATE_END_ARGS()

	void Construct (const FArguments& InArgs);

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
	

	FReply RandomiseVariables() const;
	FReply GenerateTerrain() const;
	FReply SpawnTerrainActor() const;
	FReply ClearTerrainActor() const;
	FReply SpawnDirectionalLight() const;
	FReply SaveCTM() const;
	//---------------------------------------------------
	FReply SaveFBX() const;
	FReply SaveOBJ() const;
	//---------------------------------------------------
	FReply UnimplementedButton() const;
	FReply OpenReadme() const;
};
