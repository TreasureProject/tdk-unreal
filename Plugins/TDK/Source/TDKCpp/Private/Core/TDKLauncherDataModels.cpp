// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TDKLauncherDataModels.h"

using namespace TDK;
using namespace LauncherModels;

FStartSessionRequest::~FStartSessionRequest()
{

}

void FStartSessionRequest::WriteJSON(JsonWriter& Writer) const
{

}

bool FStartSessionRequest::ReadFromValue(const TSharedPtr<FJsonObject>& Obj)
{
	return false;
}

FStartSessionResponse::~FStartSessionResponse()
{
}

void FStartSessionResponse::WriteJSON(JsonWriter& Writer) const
{
}

bool FStartSessionResponse::ReadFromValue(const TSharedPtr<FJsonObject>& Obj)
{
	return false;
}
