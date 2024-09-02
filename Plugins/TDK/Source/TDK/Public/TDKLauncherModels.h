// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDKBaseModel.h"
#include "TDKLauncherModels.generated.h"

class UTDKJsonObject;

USTRUCT(BlueprintType)
struct TDK_API FStartSessionRequest : public FTDKRequestCommon
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Launcher | Event Models")
    FString BackendWallet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Launcher | Event Models")
    TArray<FString> ApprovedTargets;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Launcher | Event Models")
    int64 NativeTokenLimitPerTransaction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Launcher | Event Models")
    int32 SessionDurationSec;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Launcher | Event Models")
    int32 SessionMinDurationLeftSec;
};

USTRUCT(BlueprintType)
struct TDK_API FStartSessionResult : public FTDKRequestCommon
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Launcher | Event Models")
    bool Result;
};