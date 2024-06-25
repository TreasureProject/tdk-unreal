// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TDKCppBaseModel.h"
#include "TDKCpp.h"

using namespace TDK;

FString FTDKCppBaseModel::toJSONString() const
{
    FString JsonOutString;
    JsonWriter Json = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR> >::Create(&JsonOutString);
    WriteJSON(Json);
    Json->Close();
    return JsonOutString;
}

void TDK::WriteMap(JsonWriter& Writer, FString Identifier, FJsonSerializableKeyValueMap Map)
{
    Writer->WriteObjectStart(Identifier);
    for (TMap<FString, FString>::TConstIterator It(Map); It; ++It)
    {
        Writer->WriteIdentifierPrefix((*It).Key);
        Writer->WriteValue((*It).Value);
    }
    Writer->WriteObjectEnd();
}
