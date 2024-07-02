// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDKBaseModel.h"
#include "TDKAnalyticsModels.generated.h"

class UTDKJsonObject;

USTRUCT(BlueprintType)
struct TDK_API FSendEventRequest : public FTDKRequestCommon
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Analytics | Event Models")
    FString SmartAccountAddress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Analytics | Event Models")
    int32 ChainId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Analytics | Event Models")
    FString CartridgeTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Analytics | Event Models")
    FString EventName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Analytics | Event Models")
    FString SessionId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Analytics | Event Models")
    FString EventId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Analytics | Event Models")
    FString TDKVersion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Analytics | Event Models")
    FString TdkFlavour;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Analytics | Event Models")
    int64 EventTimeLocal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Analytics | Event Models")
    int64 EventTimeServer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Analytics | Event Models")
    UTDKJsonObject* EventProps;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Analytics | Event Models")
    UTDKJsonObject* DeviceInfo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Analytics | Event Models")
    UTDKJsonObject* AppInfo;
};

USTRUCT(BlueprintType)
struct TDK_API FAnalyticsEmptyResult : public FTDKResultCommon
{
    GENERATED_USTRUCT_BODY()
public:
};
