// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TDKRuntimeSettings.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum EEnv
{
	DEV	= 0		UMETA(DisplayName = "Development"),
	PROD = 1	UMETA(DisplayName = "Production"),
};

UCLASS(config = Engine, defaultconfig)
class TDKCOMMON_API UTDKRuntimeSettings : public UObject
{
	GENERATED_BODY()

public:
	UTDKRuntimeSettings();

	// TDK Config
	UPROPERTY(EditAnywhere, config, Category = TDK)
	FString CartridgeTag;
	
	UPROPERTY(EditAnywhere, config, Category = TDK)
	FString DevAnalyticsApiUrl;

	UPROPERTY(EditAnywhere, config, Category = TDK)
	FString ProdAnalyticsApiUrl;

	// Third-Web Config
	UPROPERTY(EditAnywhere, config, Category = ThirdWeb)
	FString DevClientId;

	UPROPERTY(EditAnywhere, config, Category = ThirdWeb)
	FString ProdClientId;
};
