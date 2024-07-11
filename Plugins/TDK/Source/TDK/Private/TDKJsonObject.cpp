// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKJsonObject.h"
#include "TDKJsonValue.h"
#include "TDKPrivate.h"

typedef TJsonWriterFactory< TCHAR, TCondensedJsonPrintPolicy<TCHAR> > FCondensedJsonStringWriterFactory;
typedef TJsonWriter< TCHAR, TCondensedJsonPrintPolicy<TCHAR> > FCondensedJsonStringWriter;

UTDKJsonObject::UTDKJsonObject(const class FObjectInitializer& PCIP)
    : Super(PCIP)
{
    Reset();
}

UTDKJsonObject* UTDKJsonObject::ConstructJsonObject(UObject* WorldContextObject)
{
    return NewObject<UTDKJsonObject>();
}

void UTDKJsonObject::Reset()
{
    if (JsonObj.IsValid())
    {
        JsonObj.Reset();
    }

    JsonObj = MakeShareable(new FJsonObject());
}

TSharedPtr<FJsonObject>& UTDKJsonObject::GetRootObject()
{
    return JsonObj;
}

void UTDKJsonObject::SetRootObject(TSharedPtr<FJsonObject>& JsonObject)
{
    JsonObj = JsonObject;
}

FString UTDKJsonObject::EncodeJson() const
{
    if (!JsonObj.IsValid())
    {
        return TEXT("");
    }

    FString OutputString;
    TSharedRef< FCondensedJsonStringWriter > Writer = FCondensedJsonStringWriterFactory::Create(&OutputString);
    FJsonSerializer::Serialize(JsonObj.ToSharedRef(), Writer);

    return OutputString;
}

bool UTDKJsonObject::DecodeJson(const FString& JsonString)
{
    TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(*JsonString);
    if (FJsonSerializer::Deserialize(Reader, JsonObj) && JsonObj.IsValid())
    {
        return true;
    }

    // If we've failed to deserialize the string, we should clear our internal data
    Reset();

    UE_LOG(LogTDK, Error, TEXT("Json decoding failed for: %s"), *JsonString);

    return false;
}

TArray<FString> UTDKJsonObject::GetFieldNames()
{
    TArray<FString> Result;

    if (!JsonObj.IsValid())
    {
        return Result;
    }

    JsonObj->Values.GetKeys(Result);

    return Result;
}

bool UTDKJsonObject::HasField(const FString& FieldName) const
{
    if (!JsonObj.IsValid())
    {
        return false;
    }

    return JsonObj->HasField(FieldName);
}

void UTDKJsonObject::RemoveField(const FString& FieldName)
{
    if (!JsonObj.IsValid())
    {
        return;
    }

    JsonObj->RemoveField(FieldName);
}

UTDKJsonValue* UTDKJsonObject::GetField(const FString& FieldName) const
{
    if (!JsonObj.IsValid())
    {
        return nullptr;
    }

    TSharedPtr<FJsonValue> NewVal = JsonObj->TryGetField(FieldName);

    UTDKJsonValue* NewValue = NewObject<UTDKJsonValue>();
    NewValue->SetRootValue(NewVal);

    return NewValue;
}

void UTDKJsonObject::SetField(const FString& FieldName, UTDKJsonValue* JsonValue)
{
    if (!JsonObj.IsValid())
    {
        return;
    }

    JsonObj->SetField(FieldName, JsonValue->GetRootValue());
}

void UTDKJsonObject::SetFieldNull(const FString& FieldName)
{
    if (!JsonObj.IsValid())
    {
        return;
    }

    TSharedPtr<FJsonValue> myNull = MakeShareable(new FJsonValueNull());

    JsonObj->SetField(FieldName, myNull);
}

TArray<UTDKJsonValue*> UTDKJsonObject::GetArrayField(const FString& FieldName)
{
    TArray<UTDKJsonValue*> OutArray;
    if (!JsonObj.IsValid())
    {
        return OutArray;
    }

    TArray< TSharedPtr<FJsonValue> > ValArray = JsonObj->GetArrayField(FieldName);
    for (auto Value : ValArray)
    {
        UTDKJsonValue* NewValue = NewObject<UTDKJsonValue>();
        NewValue->SetRootValue(Value);

        OutArray.Add(NewValue);
    }

    return OutArray;
}

void UTDKJsonObject::SetArrayField(const FString& FieldName, const TArray<UTDKJsonValue*>& InArray)
{
    if (!JsonObj.IsValid())
    {
        return;
    }

    TArray< TSharedPtr<FJsonValue> > ValArray;

    // Process input array and COPY original values
    for (auto InVal : InArray)
    {
        TSharedPtr<FJsonValue> JsonVal = InVal->GetRootValue();

        switch (InVal->GetType())
        {
        case ETDKJson::None:
            break;

        case ETDKJson::Null:
            ValArray.Add(MakeShareable(new FJsonValueNull()));
            break;

        case ETDKJson::String:
            ValArray.Add(MakeShareable(new FJsonValueString(JsonVal->AsString())));
            break;

        case ETDKJson::Number:
            ValArray.Add(MakeShareable(new FJsonValueNumber(JsonVal->AsNumber())));
            break;

        case ETDKJson::Boolean:
            ValArray.Add(MakeShareable(new FJsonValueBoolean(JsonVal->AsBool())));
            break;

        case ETDKJson::Array:
            ValArray.Add(MakeShareable(new FJsonValueArray(JsonVal->AsArray())));
            break;

        case ETDKJson::Object:
            ValArray.Add(MakeShareable(new FJsonValueObject(JsonVal->AsObject())));
            break;

        default:
            break;
        }
    }

    JsonObj->SetArrayField(FieldName, ValArray);
}

void UTDKJsonObject::MergeJsonObject(UTDKJsonObject* InJsonObject, bool Overwrite)
{
    TArray<FString> Keys = InJsonObject->GetFieldNames();

    for (auto Key : Keys)
    {
        if (Overwrite == false && HasField(Key))
        {
            continue;
        }

        SetField(Key, InJsonObject->GetField(Key));
    }
}