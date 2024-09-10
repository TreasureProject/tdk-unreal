// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDKRuntimeSettings.h"
#include "TDKAuthenticationContext.generated.h"

/**
* Container for TDK authentication credentials data.
*/

UCLASS(BlueprintType)
class TDKCOMMON_API UTDKAuthenticationContext : public UObject
{
	GENERATED_BODY()
	
public:
	UTDKAuthenticationContext()
	{
		ApiKey = GetDefault<UTDKRuntimeSettings>()->ApiKey;
	}

    // Get the API key. These keys can be used in request authentication.
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TDK | Core")
    FString& GetApiKey()
    {
        return ApiKey;
    }

    // Get the API key. These keys can be used in request authentication.
    const FString& GetApiKey() const
    {
        return ApiKey;
    }

private:
	UPROPERTY()
	FString ApiKey;
};
