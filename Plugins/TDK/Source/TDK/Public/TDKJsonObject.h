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

	/** Create new Json object */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Construct Json Object", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "TDK | Json")
	static UTDKJsonObject* ConstructJsonObject(UObject* WorldContextObject);

	/** Reset all internal data */
	UFUNCTION(BlueprintCallable, Category = "TDK | Json")
	void Reset();

	/** Get the root Json object */
	TSharedPtr<FJsonObject>& GetRootObject();

	/** Set the root Json object */
	void SetRootObject(TSharedPtr<FJsonObject>& JsonObject);


	//////////////////////////////////////////////////////////////////////////
	// Serialization

	/** Serialize Json to string */
	UFUNCTION(BlueprintCallable, Category = "TDK | Json")
	FString EncodeJson() const;

	/** Construct Json object from string */
	UFUNCTION(BlueprintCallable, Category = "TDK | Json")
	bool DecodeJson(const FString& JsonString);


    UFUNCTION(BlueprintPure, Category = "TDK | Json")
    TArray<FString> GetFieldNames();

    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    bool HasField(const FString& FieldName) const;

    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    void RemoveField(const FString& FieldName);

    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    UTDKJsonValue* GetField(const FString& FieldName) const;

    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    void SetField(const FString& FieldName, UTDKJsonValue* JsonValue);

    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    void SetFieldNull(const FString& FieldName);

    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    TArray<UTDKJsonValue*> GetArrayField(const FString& FieldName);

    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    void SetArrayField(const FString& FieldName, const TArray<UTDKJsonValue*>& InArray);

    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    void MergeJsonObject(UTDKJsonObject* InJsonObject, bool Overwrite);


	//////////////////////////////////////////////////////////////////////////
	// Data

private:
	/** Internal JSON data */
	TSharedPtr<FJsonObject> JsonObj;
};
