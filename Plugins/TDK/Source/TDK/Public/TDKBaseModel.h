// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDKBaseModel.generated.h"

class UTDKJsonObject;

USTRUCT(BlueprintType)
struct TDK_API FTDKError
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Error | Models")
	bool hasError = false;

    void decodeError(UTDKJsonObject* responseData);
};

USTRUCT(BlueprintType)
struct TDK_API FTDKBaseModel
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Error | Models")
	FTDKError responseError = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Error | Models")
	UTDKJsonObject* responseData = nullptr;
};

USTRUCT(BlueprintType)
struct TDK_API FTDKRequestCommon
{
    GENERATED_BODY()

};

USTRUCT(BlueprintType)
struct TDK_API FTDKResultCommon
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TDK | Core")
	UTDKJsonObject* Request = nullptr;
};
