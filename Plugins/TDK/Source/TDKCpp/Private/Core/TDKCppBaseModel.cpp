// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TDKCppBaseModel.h"
#include "TDKCpp.h"

using namespace TDK;

FString FTDKCppBaseModel::toJSONString() const
{
    FString JsonOutString;
    JsonWriter Json = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR> >::Create(&JsonOutString);
    writeJSON(Json);
    Json->Close();
    return JsonOutString;
}
