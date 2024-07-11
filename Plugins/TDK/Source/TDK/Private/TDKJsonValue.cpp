// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKJsonValue.h"
#include "TDKJsonObject.h"
#include "TDKPrivate.h"

UTDKJsonValue::UTDKJsonValue(const class FObjectInitializer& PCIP)
    : Super(PCIP)
{

}

UTDKJsonValue* UTDKJsonValue::ConstructJsonValueNumber(UObject* WorldContextObject, float Number)
{
    TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueNumber(Number));

    UTDKJsonValue* NewValue = NewObject<UTDKJsonValue>();
    NewValue->SetRootValue(NewVal);

    return NewValue;
}

UTDKJsonValue* UTDKJsonValue::ConstructJsonValueString(UObject* WorldContextObject, const FString& StringValue)
{
    TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueString(StringValue));

    UTDKJsonValue* NewValue = NewObject<UTDKJsonValue>();
    NewValue->SetRootValue(NewVal);

    return NewValue;
}

UTDKJsonValue* UTDKJsonValue::ConstructJsonValueBool(UObject* WorldContextObject, bool InValue)
{
    TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueBoolean(InValue));

    UTDKJsonValue* NewValue = NewObject<UTDKJsonValue>();
    NewValue->SetRootValue(NewVal);

    return NewValue;
}

UTDKJsonValue* UTDKJsonValue::ConstructJsonValueArray(UObject* WorldContextObject, const TArray<UTDKJsonValue*>& InArray)
{
    // Prepare data array to create new value
    TArray< TSharedPtr<FJsonValue> > ValueArray;
    for (auto InVal : InArray)
    {
        ValueArray.Add(InVal->GetRootValue());
    }

    TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueArray(ValueArray));

    UTDKJsonValue* NewValue = NewObject<UTDKJsonValue>();
    NewValue->SetRootValue(NewVal);

    return NewValue;
}

UTDKJsonValue* UTDKJsonValue::ConstructJsonValueObject(UObject* WorldContextObject, UTDKJsonObject* JsonObject)
{
    TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueObject(JsonObject->GetRootObject()));

    UTDKJsonValue* NewValue = NewObject<UTDKJsonValue>();
    NewValue->SetRootValue(NewVal);

    return NewValue;
}

UTDKJsonValue* UTDKJsonValue::ConstructJsonValue(UObject* WorldContextObject, const TSharedPtr<FJsonValue>& InValue)
{
    TSharedPtr<FJsonValue> NewVal = InValue;

    UTDKJsonValue* NewValue = NewObject<UTDKJsonValue>();
    NewValue->SetRootValue(NewVal);

    return NewValue;
}

TSharedPtr<FJsonValue>& UTDKJsonValue::GetRootValue()
{
    return JsonVal;
}

void UTDKJsonValue::SetRootValue(TSharedPtr<FJsonValue>& JsonValue)
{
    JsonVal = JsonValue;
}


ETDKJson::Type UTDKJsonValue::GetType() const
{
    if (!JsonVal.IsValid())
    {
        return ETDKJson::None;
    }

    switch (JsonVal->Type)
    {
    case EJson::None:
        return ETDKJson::None;

    case EJson::Null:
        return ETDKJson::Null;

    case EJson::String:
        return ETDKJson::String;

    case EJson::Number:
        return ETDKJson::Number;

    case EJson::Boolean:
        return ETDKJson::Boolean;

    case EJson::Array:
        return ETDKJson::Array;

    case EJson::Object:
        return ETDKJson::Object;

    default:
        return ETDKJson::None;
    }
}

FString UTDKJsonValue::GetTypeString() const
{
    if (!JsonVal.IsValid())
    {
        return "None";
    }

    switch (JsonVal->Type)
    {
    case EJson::None:
        return TEXT("None");

    case EJson::Null:
        return TEXT("Null");

    case EJson::String:
        return TEXT("String");

    case EJson::Number:
        return TEXT("Number");

    case EJson::Boolean:
        return TEXT("Boolean");

    case EJson::Array:
        return TEXT("Array");

    case EJson::Object:
        return TEXT("Object");

    default:
        return TEXT("None");
    }
}

bool UTDKJsonValue::IsNull() const
{
    if (!JsonVal.IsValid())
    {
        return true;
    }

    return JsonVal->IsNull();
}

float UTDKJsonValue::AsNumber() const
{
    if (!JsonVal.IsValid())
    {
        ErrorMessage(TEXT("Number"));
        return 0.f;
    }

    return JsonVal->AsNumber();
}

FString UTDKJsonValue::AsString() const
{
    if (!JsonVal.IsValid())
    {
        ErrorMessage(TEXT("String"));
        return FString();
    }

    return JsonVal->AsString();
}

bool UTDKJsonValue::AsBool() const
{
    if (!JsonVal.IsValid())
    {
        ErrorMessage(TEXT("Boolean"));
        return false;
    }

    return JsonVal->AsBool();
}

TArray<UTDKJsonValue*> UTDKJsonValue::AsArray() const
{
    TArray<UTDKJsonValue*> OutArray;

    if (!JsonVal.IsValid())
    {
        ErrorMessage(TEXT("Array"));
        return OutArray;
    }

    TArray< TSharedPtr<FJsonValue> > ValArray = JsonVal->AsArray();
    for (auto Value : ValArray)
    {
        UTDKJsonValue* NewValue = NewObject<UTDKJsonValue>();
        NewValue->SetRootValue(Value);

        OutArray.Add(NewValue);
    }

    return OutArray;
}

UTDKJsonObject* UTDKJsonValue::AsObject()
{
    if (!JsonVal.IsValid())
    {
        ErrorMessage(TEXT("Object"));
        return nullptr;
    }

    TSharedPtr<FJsonObject> NewObj = JsonVal->AsObject();

    UTDKJsonObject* JsonObj = NewObject<UTDKJsonObject>();
    JsonObj->SetRootObject(NewObj);

    return JsonObj;
}


void UTDKJsonValue::ErrorMessage(const FString& InType) const
{
    UE_LOG(LogTDK, Error, TEXT("Json Value of type '%s' used as a '%s'."), *GetTypeString(), *InType);
}