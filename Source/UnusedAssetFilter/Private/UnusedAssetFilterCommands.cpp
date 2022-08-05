// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnusedAssetFilterCommands.h"

#define LOCTEXT_NAMESPACE "FUnusedAssetFilterModule"

void FUnusedAssetFilterCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "UnusedAssetFilter", "Bring up UnusedAssetFilter window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
