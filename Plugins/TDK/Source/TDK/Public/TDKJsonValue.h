// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonValue.h"
#include "TDKJsonValue.generated.h"

class UTDKJsonObject;

/**
 * Represents all the types a Json Value can be.
 */
UENUM(BlueprintType)
namespace ETDKJson
{
    enum Type
    {
        None,
        Null,
        String,
        Number,
        Boolean,
        Array,
        Object,
    };
}

/**
 * Blueprintable FJsonValue wrapper
 */
UCLASS(BlueprintType, Blueprintable)
class TDK_API UTDKJsonValue : public UObject
{
    GENERATED_UCLASS_BODY()

    /** Create new Json Number value */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Construct Json Number Value", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "TDK | Json")
    static UTDKJsonValue* ConstructJsonValueNumber(UObject* WorldContextObject, float Number);

    /** Create new Json String value */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Construct Json String Value", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "TDK | Json")
    static UTDKJsonValue* ConstructJsonValueString(UObject* WorldContextObject, const FString& StringValue);

    /** Create new Json Bool value */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Construct Json Bool Value", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "TDK | Json")
    static UTDKJsonValue* ConstructJsonValueBool(UObject* WorldContextObject, bool InValue);

    /** Create new Json Array value */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Construct Json Array Value", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "TDK | Json")
    static UTDKJsonValue* ConstructJsonValueArray(UObject* WorldContextObject, const TArray<UTDKJsonValue*>& InArray);

    /** Create new Json Object value */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Construct Json Object Value", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "TDK | Json")
    static UTDKJsonValue* ConstructJsonValueObject(UObject* WorldContextObject, UTDKJsonObject* JsonObject);

    /** Create new Json value from FJsonValue (to be used from TDKJsonObject) */
    static UTDKJsonValue* ConstructJsonValue(UObject* WorldContextObject, const TSharedPtr<FJsonValue>& InValue);

    /** Get the root Json value */
    TSharedPtr<FJsonValue>& GetRootValue();

    /** Set the root Json value */
    void SetRootValue(TSharedPtr<FJsonValue>& JsonValue);


    //////////////////////////////////////////////////////////////////////////
    // FJsonValue API

    /** Get type of Json value (Enum) */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    ETDKJson::Type GetType() const;

    /** Get type of Json value (String) */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    FString GetTypeString() const;

    /** Returns true if this value is a 'null' */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    bool IsNull() const;

    /** Returns this value as a double, throwing an error if this is not an Json Number
     * Attn.!! float used instead of double to make the function blueprintable! */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    float AsNumber() const;

    /** Returns this value as a number, throwing an error if this is not an Json String */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    FString AsString() const;

    /** Returns this value as a boolean, throwing an error if this is not an Json Bool */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    bool AsBool() const;

    /** Returns this value as an array, throwing an error if this is not an Json Array */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    TArray<UTDKJsonValue*> AsArray() const;

    /** Returns this value as an object, throwing an error if this is not an Json Object */
    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    UTDKJsonObject* AsObject();


    //////////////////////////////////////////////////////////////////////////
    // Data

private:
    /** Internal JSON data */
    TSharedPtr<FJsonValue> JsonVal;


    //////////////////////////////////////////////////////////////////////////
    // Helpers

protected:
    /** Simple error logger */
    void ErrorMessage(const FString& InType) const;
};
