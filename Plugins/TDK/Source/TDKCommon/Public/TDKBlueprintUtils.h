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
};
