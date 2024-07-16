// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDKBaseModel.generated.h"

class UTDKJsonObject;

USTRUCT(BlueprintType)
struct TDK_API FTDKError
{
	GENERATED_USTRUCT_BODY()

    /** Is there an error */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Error | Models")
	bool hasError = false;

    /** Holds the error code recieved from TDK. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Error | Models")
    int32 ErrorCode = 0;

    /** Holds the error name recieved from TDK. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Error | Models")
    FString ErrorName;

    /** Holds the error message recieved from TDK. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Error | Models")
    FString ErrorMessage;

    /** Holds the error details recieved from TDK. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDK | Error | Models")
    FString ErrorDetails;

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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TDK | Core")
    UTDKJsonObject* Request = nullptr;
};

USTRUCT(BlueprintType)
struct TDK_API FTDKResultCommon
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TDK | Core")
	UTDKJsonObject* Request = nullptr;
};
