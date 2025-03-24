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

	// ---------------- General ----------------- //

	UPROPERTY(EditAnywhere, config, Category = General)
	TEnumAsByte<EEnv> Env;

	UPROPERTY(EditAnywhere, config, Category = General)
	FString CartridgeTag;

	UPROPERTY(EditAnywhere, config, Category = General)
	FString CartridgeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General)
	UTexture2D* CartridgeIcon;

	UPROPERTY(EditAnywhere, config, Category = General)
	FString ProdApiUrl;

	UPROPERTY(EditAnywhere, config, Category = General)
	FString DevApiUrl;

	UPROPERTY(EditAnywhere, config, Category = General)
	FString ClientId;

	UPROPERTY(EditAnywhere, config, Category = General)
	FString EcosystemId;

	UPROPERTY(EditAnywhere, config, Category = General)
	FString EcosystemPartnerId;

	UPROPERTY(EditAnywhere, config, Category = General)
	FString DevApiKey;

	UPROPERTY(EditAnywhere, config, Category = General)
	FString ProdApiKey;


	// ----------------- Connect ------------------- //

	UPROPERTY(EditAnywhere, config, Category = Connect)
	FString FactoryAddress;

    UPROPERTY(EditAnywhere, config, Category = Connect)
    int64 DevChainId;

    UPROPERTY(EditAnywhere, config, Category = Connect)
    int64 ProdChainId;

	UPROPERTY(EditAnywhere, config, Category = Connect)
	int32 SessionDurationSec;

	UPROPERTY(EditAnywhere, config, Category = Connect)
	int32 SessionMinDurationLeftSec;

	UPROPERTY(EditAnywhere, config, Category = "Connect|SessionOptions")
	FString ChainIdentifier;

	UPROPERTY(EditAnywhere, config, Category = "Connect|SessionOptions")
	FString BackendWallet;

	UPROPERTY(EditAnywhere, config, Category = "Connect|SessionOptions")
	TArray<FString> CallTargets;

	UPROPERTY(EditAnywhere, config, Category = "Connect|SessionOptions")
	FString NativeTokenLimitPerTransaction;


	// ---------------- Analytics ------------------- //

	UPROPERTY(EditAnywhere, config, Category = Analytics)
	FString DevAnalyticsApiUrl;

	UPROPERTY(EditAnywhere, config, Category = Analytics)
	FString ProdAnalyticsApiUrl;


	// ---------------- Launcher ------------------- //

	UPROPERTY(EditAnywhere, config, Category = Launcher)
	FString LauncherApiUrl;

public:
	FString GetAnalyticsApiUrl() const;

	FString GetApiKey() const;

	FString GetLauncherApiUrl() const;

	int64 GetChainId() const;
};
