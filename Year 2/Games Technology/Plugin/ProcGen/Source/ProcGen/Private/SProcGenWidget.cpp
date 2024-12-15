#include "SProcGenWidget.h"
#include "Randomizer.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SSpinBox.h"
#include "VarContainer.h"
#include "GeneratorCore.h"
#include "FileHandler.h"
#include "Engine/DirectionalLight.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Components/LightComponent.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SProcGenWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot().AutoWidth().Padding(15)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().AutoHeight().Padding(2)
			[
				SNew(STextBlock)
				.Text(FText::FromString("Variables"))
			]

			+ SVerticalBox::Slot().AutoHeight().Padding(2)
			[
				SNew(SHorizontalBox)
				// Variables horizontal box
				+ SHorizontalBox::Slot().AutoWidth().Padding(2)
				[
					// Variable names vertical box
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Terrain Width (1-255)"))
					]

					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Terrain Length (1-255)"))
					]

					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Sea Level (0-1)"))
					]

					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Minimum River Starting Height (1-255)"))
					]

					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Maximum River Starting Height (1-255)"))
					]

					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Hard Floor Height (-1-1)"))
					]

					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Number of Octaves (1-5)"))
					]

					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Scale Factor (0.001-1)"))
					]

					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Height Multiplier (1-100)"))
					]

					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Persistence (0.001-1)"))
					]
				]

				// Variable sliders horizontal box
				+ SHorizontalBox::Slot().FillWidth(10).Padding(2)
				[
					// Variables vertical box
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(SSpinBox<uint8>)
						.MinValue(1)
						.MaxValue(255)
						.Value(this, &SProcGenWidget::GetTerrainWidth)
						.OnValueChanged(this, &SProcGenWidget::SetTerrainWidth)
					]

					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(SSpinBox<uint8>)
						.MinValue(1)
						.MaxValue(255)
						.Value(this, &SProcGenWidget::GetTerrainLength)
						.OnValueChanged(this, &SProcGenWidget::SetTerrainLength)
					]

					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(SSpinBox<float>)
						.MinValue(0.001)
						.MaxValue(1)
						.Value(this, &SProcGenWidget::GetSeaLevel)
						.OnValueChanged(this, &SProcGenWidget::SetSeaLevel)
					]

					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(SSpinBox<uint8>)
						.MinValue(1)
						.MaxValue(255)
						.Value(this, &SProcGenWidget::GetMinStartRiverHeight)
						.OnValueChanged(this, &SProcGenWidget::SetMinStartRiverHeight)
					]

					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(SSpinBox<uint8>)
						.MinValue(1)
						.MaxValue(255)
						.Value(this, &SProcGenWidget::GetMaxStartRiverHeight)
						.OnValueChanged(this, &SProcGenWidget::SetMaxStartRiverHeight)
					]

					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(SSpinBox<float>)
						.MinValue(-1)
						.MaxValue(1)
						.Value(this, &SProcGenWidget::GetHardFloorHeight)
						.OnValueChanged(this, &SProcGenWidget::SetHardFloorHeight)
					]

					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(SSpinBox<uint8>)
						.MinValue(1)
						.MaxValue(5)
						.Value(this, &SProcGenWidget::GetOctaves)
						.OnValueChanged(this, &SProcGenWidget::SetOctaves)
					]

					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(SSpinBox<float>)
						.MinValue(0.001)
						.MaxValue(1)
						.Value(this, &SProcGenWidget::GetScaleFactor)
						.OnValueChanged(this, &SProcGenWidget::SetScaleFactor)
					]

					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(SSpinBox<uint8>)
						.MinValue(1)
						.MaxValue(100)
						.Value(this, &SProcGenWidget::GetHeightMultiplier)
						.OnValueChanged(this, &SProcGenWidget::SetHeightMultiplier)
					]

					+ SVerticalBox::Slot().AutoHeight().Padding(2, 10, 2, 10)
					[
						SNew(SSpinBox<float>)
						.MinValue(0.001)
						.MaxValue(1)
						.Value(this, &SProcGenWidget::GetPersistence)
						.OnValueChanged(this, &SProcGenWidget::SetPersistence)
					]
				]
			]
		]

		+ SHorizontalBox::Slot().AutoWidth().Padding(15)
		[
			SNew(SVerticalBox)
			// Generation
			+ SVerticalBox::Slot().AutoHeight().Padding(2)
			[
				SNew(STextBlock)
				.Text(FText::FromString("Generator"))
			]

			+ SVerticalBox::Slot().AutoHeight().Padding(2)
			[
				SNew(SButton)
				.Text(FText::FromString("Randomise Variables"))
				.OnClicked(this, &SProcGenWidget::RandomiseVariables)
			]

			+ SVerticalBox::Slot().AutoHeight().Padding(2)
			[
				SNew(SButton)
				.Text(FText::FromString("Generate Terrain"))
				.OnClicked(this, &SProcGenWidget::GenerateTerrain)
			]

			+ SVerticalBox::Slot().AutoHeight().Padding(2)
			[
				SNew(SButton)
				.Text(FText::FromString("Spawn TerrainMeshActor"))
				.OnClicked(this, &SProcGenWidget::SpawnTerrainActor)
			]
			
			+ SVerticalBox::Slot().AutoHeight().Padding(2)
			[
				SNew(SButton)
				.Text(FText::FromString("Clear Current TerrainMeshActor"))
				.OnClicked(this, &SProcGenWidget::ClearTerrainActor)
			]

			+ SVerticalBox::Slot().AutoHeight().Padding(2)
			[
				SNew(SButton)
				.Text(FText::FromString("Spawn DirectionalLight"))
				.OnClicked(this, &SProcGenWidget::SpawnDirectionalLight)
			]
			// File saving
			+ SVerticalBox::Slot().AutoHeight().Padding(2)
			[
				SNew(STextBlock)
				.Text(FText::FromString("Save options"))
			]

			+ SVerticalBox::Slot().AutoHeight().Padding(2)
			[
				SNew(SButton)
				.Text(FText::FromString("Save as CTM"))
				.OnClicked(this, &SProcGenWidget::SaveCTM)
			]

			+ SVerticalBox::Slot().AutoHeight().Padding(2)
			[
				SNew(SButton)
				.Text(FText::FromString("Save as FBX"))
				.OnClicked(this, &SProcGenWidget::UnimplementedButton)
			]

			+ SVerticalBox::Slot().AutoHeight().Padding(2)
			[
				SNew(SButton)
				.Text(FText::FromString("Save as OBJ"))
				.OnClicked(this, &SProcGenWidget::UnimplementedButton)
			]

			// Readme stuff
			+ SVerticalBox::Slot().AutoHeight().Padding(40)
			[
				SNew(SButton)
				.Text(FText::FromString("Open plugin README"))
				.OnClicked(this, &SProcGenWidget::OpenReadme)
			]
		]
	];
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION


void SProcGenWidget::SetTerrainWidth(uint8 var)
{
	FVarContainer::GetInstance()->SetTerrainWidth(var);
}

void SProcGenWidget::SetTerrainLength(uint8 var)
{
	FVarContainer::GetInstance()->SetTerrainLength(var);
}

void SProcGenWidget::SetSeaLevel(float var)
{
	FVarContainer::GetInstance()->SetSeaLevel(var);
}

void SProcGenWidget::SetMinStartRiverHeight(uint8 var)
{
	FVarContainer::GetInstance()->SetMinStartRiverHeight(var);
}

void SProcGenWidget::SetMaxStartRiverHeight(uint8 var)
{
	FVarContainer::GetInstance()->SetMaxStartRiverHeight(var);
}

void SProcGenWidget::SetHardFloorHeight(float var)
{
	FVarContainer::GetInstance()->SetHardFloorHeight(var);
}

void SProcGenWidget::SetOctaves(uint8 var)
{
	FVarContainer::GetInstance()->SetOctaves(var);
}

void SProcGenWidget::SetScaleFactor(float var)
{
	FVarContainer::GetInstance()->SetScaleFactor(var);
}

void SProcGenWidget::SetHeightMultiplier(uint8 var)
{
	FVarContainer::GetInstance()->SetHeightMultiplier(var);
}

void SProcGenWidget::SetPersistence(float var)
{
	FVarContainer::GetInstance()->SetPersistence(var);
}


uint8 SProcGenWidget::GetTerrainWidth() const
{
	return FVarContainer::GetInstance()->GetTerrainWidth();
}

uint8 SProcGenWidget::GetTerrainLength() const
{
	return FVarContainer::GetInstance()->GetTerrainLength();
}

float SProcGenWidget::GetSeaLevel() const
{
	return FVarContainer::GetInstance()->GetSeaLevel();
}

uint8 SProcGenWidget::GetMinStartRiverHeight() const
{
	return FVarContainer::GetInstance()->GetMinStartRiverHeight();
}

uint8 SProcGenWidget::GetMaxStartRiverHeight() const
{
	return FVarContainer::GetInstance()->GetMaxStartRiverHeight();
}

float SProcGenWidget::GetHardFloorHeight() const
{
	return FVarContainer::GetInstance()->GetHardFloorHeight();
}

uint8 SProcGenWidget::GetOctaves() const
{
	return FVarContainer::GetInstance()->GetOctaves();
}

float SProcGenWidget::GetScaleFactor() const
{
	return FVarContainer::GetInstance()->GetScaleFactor();
}

uint8 SProcGenWidget::GetHeightMultiplier() const
{
	return FVarContainer::GetInstance()->GetHeightMultiplier();
}

float SProcGenWidget::GetPersistence() const
{
	return FVarContainer::GetInstance()->GetPersistence();
}


FReply SProcGenWidget::RandomiseVariables() const
{
	FRandomizer RandomInstance = FRandomizer();
	RandomInstance.RandomiseVariables();

	return FReply::Handled();
}

FReply SProcGenWidget::GenerateTerrain() const
{
	ATerrainMesh* TerrainMesh = FVarContainer::GetInstance()->GetTerrainMeshInstance();
	if (TerrainMesh == nullptr)
	{
		FText NotificationText = FText::FromString("No valid TerrainMesh instance, create one using the plugin");

		FNotificationInfo Info(NotificationText);
		Info.bFireAndForget = true;
		Info.ExpireDuration = 5.0f;
		Info.bUseSuccessFailIcons = true;
		Info.Image = FCoreStyle::Get().GetBrush(TEXT("MessageLog.Warning"));

		FSlateNotificationManager::Get().AddNotification(Info);

		return FReply::Unhandled();
	}

	FGeneratorCore NewCore = FGeneratorCore();
	NewCore.GenerateMesh();

	return FReply::Handled();
}

FReply SProcGenWidget::SpawnTerrainActor() const
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if(World)
	{
		ATerrainMesh* TerrainMeshActor = FVarContainer::GetInstance()->GetTerrainMeshInstance();
		if (!TerrainMeshActor || !TerrainMeshActor->IsValidLowLevel())
		{
			TerrainMeshActor = World->SpawnActor<ATerrainMesh>();
			FVarContainer::GetInstance()->SetTerrainMeshInstance(TerrainMeshActor);
		}
	}
	return FReply::Handled();
}

FReply SProcGenWidget::ClearTerrainActor() const
{
	FVarContainer::GetInstance()->GetTerrainMeshInstance()->ClearMesh();

	return FReply::Handled();
}

FReply SProcGenWidget::SpawnDirectionalLight() const
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World)
	{
		FVector Location = FVector(0.0f, 0.0f, 0.0f);
		FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);

		ADirectionalLight* DirectionalLight = World->SpawnActor<ADirectionalLight>(Location, Rotation);

		if (DirectionalLight)
		{
			DirectionalLight->GetLightComponent()->SetIntensity(3.0f);
		}
	}

	return FReply::Handled();
}

FReply SProcGenWidget::SaveCTM() const
{
	FFileHandler Handler = FFileHandler();
	Handler.DialogueContextCTM();
	
	return FReply::Handled();
}
//---------------------------------------------------
FReply SProcGenWidget::SaveFBX() const
{
	// NOT IMPLEMENTED

	return FReply::Handled();
}

FReply SProcGenWidget::SaveOBJ() const
{
	// NOT IMPLEMENTED

	return FReply::Handled();
}
//---------------------------------------------------
FReply SProcGenWidget::UnimplementedButton() const
{
	FText NotificationText = FText::FromString("This button hasn't been implemented yet.");

	FNotificationInfo Info(NotificationText);
	Info.bFireAndForget = true;
	Info.ExpireDuration = 5.0f;
	Info.bUseSuccessFailIcons = true;
	Info.Image = FCoreStyle::Get().GetBrush(TEXT("MessageLog.Warning"));

	FSlateNotificationManager::Get().AddNotification(Info);

	return FReply::Handled();
}

FReply SProcGenWidget::OpenReadme() const
{
	FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("ProcGen"),
		TEXT("Source"), TEXT("ProcGen"), TEXT("README.md")));
	FString AppPath = TEXT("C:/Windows/System32/notepad.exe");
	FString Params = FString::Printf(TEXT("\"%s\""), *FilePath);
	FPlatformProcess::CreateProc(*AppPath, *Params, true, false,
		false, nullptr, 0, nullptr, nullptr);

	return FReply::Handled();
}
