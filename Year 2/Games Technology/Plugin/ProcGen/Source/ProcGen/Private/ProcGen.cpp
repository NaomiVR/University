// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProcGen.h"
#include "ProcGenStyle.h"
#include "ProcGenCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "SProcGenWidget.h"
#include "TerrainMesh.h"
#include "VarContainer.h"


static const FName ProcGenTabName("Procedural Terrain Generator");

#define LOCTEXT_NAMESPACE "FProcGenModule"

void FProcGenModule::StartupModule()
{
	FProcGenStyle::Initialize();
	FProcGenStyle::ReloadTextures();
	FProcGenCommands::Register();
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FProcGenCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FProcGenModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FProcGenModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ProcGenTabName, FOnSpawnTab::CreateRaw(this, &FProcGenModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FProcGenTabTitle", "ProcGen"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FProcGenModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
	FProcGenStyle::Shutdown();
	FProcGenCommands::Unregister();
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ProcGenTabName);
}

TSharedRef<SDockTab> FProcGenModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SProcGenWidget)
		];
}

void FProcGenModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(ProcGenTabName);


	// Get the world
	
}

void FProcGenModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);
	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FProcGenCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FProcGenCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FProcGenModule, ProcGen)