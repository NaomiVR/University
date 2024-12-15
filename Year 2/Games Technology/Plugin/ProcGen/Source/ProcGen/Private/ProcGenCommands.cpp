// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProcGenCommands.h"

#define LOCTEXT_NAMESPACE "FProcGenModule"

void FProcGenCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "ProcGen", "Bring up ProcGen window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
