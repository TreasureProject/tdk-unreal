// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Http.h"
#include "Net/OnlineBlueprintCallProxyBase.h"

#include "TDKAnalyticsAPI.generated.h"
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TDK_API UTDKAnalyticsAPI : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, Category = "TDK | Analytics | Events ", meta = (BlueprintInternalUseOnly = "true"))
	static void LoginWithCustomID();
};
