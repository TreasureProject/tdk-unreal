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

};

USTRUCT(BlueprintType)
struct TDK_API FStartSessionResult : public FTDKRequestCommon
{
    GENERATED_USTRUCT_BODY()

public:

};