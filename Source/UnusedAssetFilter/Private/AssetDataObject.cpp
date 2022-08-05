// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetDataObject.h"
#include "AssetManagerEditorModule.h"

void UAssetDataObject::GetAssetDiskSize(int64& size)
{
	if (FModuleManager::Get().ModuleExists(TEXT("AssetManagerEditor"))) {
		IAssetManagerEditorModule& Module = FModuleManager::LoadModuleChecked< IAssetManagerEditorModule >("AssetManagerEditor");
		const FAssetManagerEditorRegistrySource* registry = Module.GetCurrentRegistrySource();
		if (registry && registry->RegistryState) {
			Module.GetIntegerValueForCustomColumn(AssetData, Module.DiskSizeName, size);
			DiskSize = size;
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AssetManagerEditor plugin is not enabled"));
	}
}
