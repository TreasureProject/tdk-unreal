// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "TDKAnalyticsModels.h"

#include "TDKAnalyticsModelDecoder.generated.h"

class UTDKJsonObject;

UCLASS()
class TDK_API UTDKAnalyticsModelDecoder : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Decode the LoginResult response object*/
	UFUNCTION(BlueprintCallable, Category = "PlayFab | Client | Authentication Models")
	static FSendEventResult DecodeSendEventResponse(UTDKJsonObject* Response);
};