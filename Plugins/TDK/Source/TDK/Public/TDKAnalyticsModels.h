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
    FString EventName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Analytics | Event Models")
    TMap<FString, FString> EventProps;
};

USTRUCT(BlueprintType)
struct TDK_API FSendEventResult : public FTDKRequestCommon
{
    GENERATED_USTRUCT_BODY()
public:
    
};

USTRUCT(BlueprintType)
struct TDK_API FAnalyticsEmptyResult : public FTDKResultCommon
{
    GENERATED_USTRUCT_BODY()
public:
};
