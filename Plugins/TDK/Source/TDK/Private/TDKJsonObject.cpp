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


//////////////////////////////////////////////////////////////////////////
// Serialization

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


//////////////////////////////////////////////////////////////////////////
// FJsonObject API

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

//////////////////////////////////////////////////////////////////////////
// FJsonObject API Helpers (easy to use with simple Json objects)

int32 UTDKJsonObject::GetIntegerField(const FString& FieldName) const
{
    if (!JsonObj.IsValid())
    {
        return 0;
    }

    return JsonObj->GetIntegerField(FieldName);
}

void UTDKJsonObject::SetIntegerField(const FString& FieldName, int32 Number)
{
    if (!JsonObj.IsValid())
    {
        return;
    }

    JsonObj->SetNumberField(FieldName, Number);
}

FString UTDKJsonObject::GetStringField(const FString& FieldName) const
{
    if (!JsonObj.IsValid())
    {
        return TEXT("");
    }

    return JsonObj->GetStringField(FieldName);
}

void UTDKJsonObject::SetStringField(const FString& FieldName, const FString& StringValue)
{
    if (!JsonObj.IsValid())
    {
        return;
    }

    JsonObj->SetStringField(FieldName, StringValue);
}

bool UTDKJsonObject::GetBoolField(const FString& FieldName) const
{
    if (!JsonObj.IsValid())
    {
        return false;
    }

    return JsonObj->GetBoolField(FieldName);
}

void UTDKJsonObject::SetBoolField(const FString& FieldName, bool InValue)
{
    if (!JsonObj.IsValid())
    {
        return;
    }

    JsonObj->SetBoolField(FieldName, InValue);
}

UTDKJsonObject* UTDKJsonObject::GetObjectField(const FString& FieldName) const
{
    if (!JsonObj.IsValid())
    {
        return nullptr;
    }

    TSharedPtr<FJsonObject> JsonObjField = JsonObj->GetObjectField(FieldName);

    UTDKJsonObject* OutRestJsonObj = NewObject<UTDKJsonObject>();
    OutRestJsonObj->SetRootObject(JsonObjField);

    return OutRestJsonObj;
}

void UTDKJsonObject::SetObjectField(const FString& FieldName, UTDKJsonObject* JsonObject)
{
    if (!JsonObj.IsValid())
    {
        return;
    }

    JsonObj->SetObjectField(FieldName, JsonObject->GetRootObject());
}