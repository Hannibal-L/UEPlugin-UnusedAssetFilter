// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnusedAssetFilter.h"
#include "UnusedAssetFilterStyle.h"
#include "UnusedAssetFilterCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "Blueprint/UserWidget.h"
#include "Editor/Blutility/Classes/EditorUtilityWidgetBlueprint.h"
#include "UObject/ConstructorHelpers.h"
#include "Blutility/Classes/EditorUtilityWidget.h"

static const FName UnusedAssetFilterTabName("UnusedAssetFilter");

#define LOCTEXT_NAMESPACE "FUnusedAssetFilterModule"

void FUnusedAssetFilterModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FUnusedAssetFilterStyle::Initialize();
	FUnusedAssetFilterStyle::ReloadTextures();

	FUnusedAssetFilterCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FUnusedAssetFilterCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FUnusedAssetFilterModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FUnusedAssetFilterModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(UnusedAssetFilterTabName, FOnSpawnTab::CreateRaw(this, &FUnusedAssetFilterModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FUnusedAssetFilterTabTitle", "UnusedAssetFilter"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FUnusedAssetFilterModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FUnusedAssetFilterStyle::Shutdown();

	FUnusedAssetFilterCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(UnusedAssetFilterTabName);
}

TSharedRef<SDockTab> FUnusedAssetFilterModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	const TCHAR* WidgetPath = TEXT("/UnusedAssetFilter/EWBP_UnusedAssetFilter.EWBP_UnusedAssetFilter_C");
	const auto WidgetClass = LoadClass<UEditorUtilityWidget>(nullptr, WidgetPath);
	UEditorUtilityWidget* UserWidget = CreateWidget<UEditorUtilityWidget>(GWorld->GetWorld(), WidgetClass);
	const TSharedRef<SWidget> SlateWidget = UserWidget->TakeWidget();

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SlateWidget
			]
		];
}

void FUnusedAssetFilterModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(UnusedAssetFilterTabName);
}

void FUnusedAssetFilterModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FUnusedAssetFilterCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FUnusedAssetFilterCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUnusedAssetFilterModule, UnusedAssetFilter)