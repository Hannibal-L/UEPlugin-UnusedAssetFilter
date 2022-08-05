// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AssetDataObject.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UNUSEDASSETFILTER_API UAssetDataObject: public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAssetData AssetData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 DiskSize;

	UFUNCTION(BlueprintCallable)
	void GetAssetDiskSize(int64& size);
};
