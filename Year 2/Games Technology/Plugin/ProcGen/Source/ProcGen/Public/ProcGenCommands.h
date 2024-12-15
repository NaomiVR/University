// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ProcGenStyle.h"

class FProcGenCommands : public TCommands<FProcGenCommands>
{
public:

	FProcGenCommands()
		: TCommands<FProcGenCommands>(TEXT("ProcGen"), NSLOCTEXT("Contexts", "ProcGen", "ProcGen Plugin"), NAME_None, FProcGenStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};