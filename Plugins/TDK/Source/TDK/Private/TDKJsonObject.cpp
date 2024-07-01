// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKJsonObject.h"
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
