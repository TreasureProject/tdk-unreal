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


    //////////////////////////////////////////////////////////////////////////
    // FJsonObject API

    /** Returns a list of field names that exist in the object */
    UFUNCTION(BlueprintPure, Category = "TDK | Json")
    TArray<FString> GetFieldNames();

    /** Checks to see if the FieldName exists in the object */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    bool HasField(const FString& FieldName) const;

    /** Remove field named FieldName */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    void RemoveField(const FString& FieldName);

    /** Get the field named FieldName as a JsonValue */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    UTDKJsonValue* GetField(const FString& FieldName) const;

    /** Add a field named FieldName with a Value */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    void SetField(const FString& FieldName, UTDKJsonValue* JsonValue);

    /** Add a field named FieldName with a null value */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    void SetFieldNull(const FString& FieldName);

    /** Adds all of the fields from one json object to this one */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    void MergeJsonObject(UTDKJsonObject* InJsonObject, bool Overwrite);


	//////////////////////////////////////////////////////////////////////////
	// FJsonObject API Helpers (easy to use with simple Json objects)

    /** Get the field named FieldName as a integer */
    UFUNCTION(BlueprintCallable, Category = "PlayFab | Json")
    int32 GetIntegerField(const FString& FieldName) const;

    /** Add a field named FieldName with Integer as value */
    UFUNCTION(BlueprintCallable, Category = "PlayFab | Json")
    void SetIntegerField(const FString& FieldName, int32 Number);

    /** Get the field named FieldName as a string. */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    FString GetStringField(const FString& FieldName) const;

    /** Add a field named FieldName with value of StringValue */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    void SetStringField(const FString& FieldName, const FString& StringValue);

    /** Get the field named FieldName as a boolean. */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    bool GetBoolField(const FString& FieldName) const;

    /** Set a boolean field named FieldName and value of InValue */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    void SetBoolField(const FString& FieldName, bool InValue);

    /** Get the field named FieldName as a Json object. */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    UTDKJsonObject* GetObjectField(const FString& FieldName) const;

    /** Set an ObjectField named FieldName and value of JsonObject */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    void SetObjectField(const FString& FieldName, UTDKJsonObject* JsonObject);


	//////////////////////////////////////////////////////////////////////////
	// Data

private:
	/** Internal JSON data */
	TSharedPtr<FJsonObject> JsonObj;
};
