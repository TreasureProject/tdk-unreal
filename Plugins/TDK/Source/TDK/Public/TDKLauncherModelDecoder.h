// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "TDKLauncherModels.h"

#include "TDKLauncherModelDecoder.generated.h"

/**
 * 
 */
UCLASS()
class TDK_API UTDKLauncherModelDecoder : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Decode the StartSession response object*/
	UFUNCTION(BlueprintCallable, Category = "TDK | Client | Authentication Models")
	static FStartSessionResult DecodeStartSessionResponse(UTDKJsonObject* Response);
};
