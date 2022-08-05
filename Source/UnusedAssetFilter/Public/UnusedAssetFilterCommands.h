// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "UnusedAssetFilterStyle.h"

class FUnusedAssetFilterCommands : public TCommands<FUnusedAssetFilterCommands>
{
public:

	FUnusedAssetFilterCommands()
		: TCommands<FUnusedAssetFilterCommands>(TEXT("UnusedAssetFilter"), NSLOCTEXT("Contexts", "UnusedAssetFilter", "UnusedAssetFilter Plugin"), NAME_None, FUnusedAssetFilterStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};