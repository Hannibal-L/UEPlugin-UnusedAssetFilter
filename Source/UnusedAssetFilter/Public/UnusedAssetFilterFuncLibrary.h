// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetDataObject.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UnusedAssetFilterFuncLibrary.generated.h"

UENUM(BlueprintType)
enum class EUnusedAssetSortType: uint8
{
	ClassType,
	AssetName,
	AssetPath,
	DiskSize,
};

/**
 * 
 */
UCLASS()
class UNUSEDASSETFILTER_API UUnusedAssetFilterFuncLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static void SortAssetDataObjectArray(UPARAM(ref)TArray<UAssetDataObject*>& ObjectArray, EUnusedAssetSortType SortType, bool Descending, TArray<UAssetDataObject*>& SortedArray);

	UFUNCTION(BlueprintCallable)
	static void BrowserToAssetData(UPARAM(ref)TArray<FAssetData>& AssetDatas);

	UFUNCTION(BlueprintCallable)
	static void OpenRefGraph(UPARAM(ref)TArray<FAssetData>& AssetDatas);

	UFUNCTION(BlueprintCallable)
	static void DeleteAssets(UPARAM(ref)TArray<FAssetData>& AssetDatas);
};
