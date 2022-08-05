// Fill out your copyright notice in the Description page of Project Settings.


#include "UnusedAssetFilterFuncLibrary.h"

#include "AssetManagerEditorModule.h"
#include "ObjectTools.h"

void UUnusedAssetFilterFuncLibrary::SortAssetDataObjectArray(TArray<UAssetDataObject*>& ObjectArray, EUnusedAssetSortType SortType,
                                                             bool Descending, TArray<UAssetDataObject*>& SortedArray)
{
	if (SortType == EUnusedAssetSortType::AssetName) {
		ObjectArray.Sort([Descending](const UAssetDataObject& A, const UAssetDataObject& B) {
			if (Descending) {
				return A.AssetData.AssetName.ToString() > B.AssetData.AssetName.ToString();
			}
			else {
				return A.AssetData.AssetName.ToString() < B.AssetData.AssetName.ToString();
			}
		});
	} else if (SortType == EUnusedAssetSortType::AssetPath) {
		ObjectArray.Sort([Descending](const UAssetDataObject& A, const UAssetDataObject& B) {
			if (Descending) {
				return A.AssetData.PackagePath.ToString() > B.AssetData.PackagePath.ToString();
			}
			else {
				return A.AssetData.PackagePath.ToString() < B.AssetData.PackagePath.ToString();
			}
		});
	} else if (SortType == EUnusedAssetSortType::ClassType) {
		ObjectArray.Sort([Descending](const UAssetDataObject& A, const UAssetDataObject& B) {
			if (Descending) {
				return A.AssetData.AssetClass.ToString() > B.AssetData.AssetClass.ToString();
			}
			else {
				return A.AssetData.AssetClass.ToString() < B.AssetData.AssetClass.ToString();
			}
		});
	} else if (SortType == EUnusedAssetSortType::DiskSize) {
		ObjectArray.Sort([Descending](const UAssetDataObject& A, const UAssetDataObject& B) {
			if (Descending) {
				return A.DiskSize > B.DiskSize;
			}
			else {
				return A.DiskSize < B.DiskSize;
			}
		});
	}
	SortedArray = ObjectArray;
}

void UUnusedAssetFilterFuncLibrary::BrowserToAssetData(TArray<FAssetData>& AssetDatas)
{
	GEditor->SyncBrowserToObjects(AssetDatas);
}

void UUnusedAssetFilterFuncLibrary::OpenRefGraph(TArray<FAssetData>& AssetDatas)
{
	if (FModuleManager::Get().IsModuleLoaded("AssetManagerEditor"))
	{
		IAssetManagerEditorModule& Module = FModuleManager::LoadModuleChecked<IAssetManagerEditorModule>("AssetManagerEditor");
		TArray<FName> Assets;
		for (auto AssetData: AssetDatas)
		{
			Assets.AddUnique(AssetData.PackageName);
		}
		Module.OpenReferenceViewerUI(Assets);
	}
}

void UUnusedAssetFilterFuncLibrary::DeleteAssets(TArray<FAssetData>& AssetDatas)
{
	ObjectTools::DeleteAssets(AssetDatas, true);
}
