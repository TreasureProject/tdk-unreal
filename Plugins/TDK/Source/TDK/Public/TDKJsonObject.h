// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "TDKJsonObject.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TDK_API UTDKJsonObject : public UObject
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Construct Json Object", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "TDK | Json")
	static UTDKJsonObject* ConstructJsonObject(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "TDK | Json")
	void Reset();

	TSharedPtr<FJsonObject>& GetRootObject();

	void SetRootObject(TSharedPtr<FJsonObject>& JsonObject);

	UFUNCTION(BlueprintCallable, Category = "TDK | Json")
	FString EncodeJson() const;

	UFUNCTION(BlueprintCallable, Category = "TDK | Json")
	bool DecodeJson(const FString& JsonString);

private:
	TSharedPtr<FJsonObject> JsonObj;
};
