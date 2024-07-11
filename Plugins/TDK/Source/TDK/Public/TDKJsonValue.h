// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonValue.h"
#include "TDKJsonValue.generated.h"

class UTDKJsonObject;

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

UCLASS(BlueprintType, Blueprintable)
class TDK_API UTDKJsonValue : public UObject
{
    GENERATED_UCLASS_BODY()

    UFUNCTION(BlueprintPure, meta = (DisplayName = "Construct Json Number Value", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "TDK | Json")
    static UTDKJsonValue* ConstructJsonValueNumber(UObject* WorldContextObject, float Number);

    UFUNCTION(BlueprintPure, meta = (DisplayName = "Construct Json String Value", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "TDK | Json")
    static UTDKJsonValue* ConstructJsonValueString(UObject* WorldContextObject, const FString& StringValue);

    UFUNCTION(BlueprintPure, meta = (DisplayName = "Construct Json Bool Value", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "TDK | Json")
    static UTDKJsonValue* ConstructJsonValueBool(UObject* WorldContextObject, bool InValue);

    UFUNCTION(BlueprintPure, meta = (DisplayName = "Construct Json Array Value", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "TDK | Json")
    static UTDKJsonValue* ConstructJsonValueArray(UObject* WorldContextObject, const TArray<UTDKJsonValue*>& InArray);

    UFUNCTION(BlueprintPure, meta = (DisplayName = "Construct Json Object Value", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "TDK | Json")
    static UTDKJsonValue* ConstructJsonValueObject(UObject* WorldContextObject, UTDKJsonObject* JsonObject);

    static UTDKJsonValue* ConstructJsonValue(UObject* WorldContextObject, const TSharedPtr<FJsonValue>& InValue);

    TSharedPtr<FJsonValue>& GetRootValue();

    void SetRootValue(TSharedPtr<FJsonValue>& JsonValue);



    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    ETDKJson::Type GetType() const;

    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    FString GetTypeString() const;

    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    bool IsNull() const;

    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    float AsNumber() const;

    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    FString AsString() const;

    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    bool AsBool() const;

    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    TArray<UTDKJsonValue*> AsArray() const;

    UFUNCTION(BlueprintCallable, Category = "TDK | Json")
    UTDKJsonObject* AsObject();



private:
    TSharedPtr<FJsonValue> JsonVal;



protected:
    void ErrorMessage(const FString& InType) const;
};
