// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TDKTimeAPI.generated.h"

/**
 * 
 */
UCLASS()
class TDK_API UTDKTimeAPI : public UObject
{
	GENERATED_BODY()
	
public:
	static int64 GetLocalTime();
};
