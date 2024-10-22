// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TDKBlueprintUtils.generated.h"

/**
 * 
 */
UCLASS()
class TDKCOMMON_API UTDKBlueprintUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	static bool IsEmailValid(const FString& email);

	UFUNCTION(BlueprintCallable)
	static void CopyText(const FString& text);

	UFUNCTION(BlueprintPure)
	static FString GetCartridgeName();

	UFUNCTION(BlueprintPure)
	static UTexture2D* GetCartridgeIcon();
};
