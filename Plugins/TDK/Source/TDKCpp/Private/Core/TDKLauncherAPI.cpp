// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TDKLauncherAPI.h"

using namespace TDK;
using namespace LauncherModels;

TDKLauncherAPI::TDKLauncherAPI()
{
}

TDKLauncherAPI::~TDKLauncherAPI()
{
}

bool TDKLauncherAPI::StartTDKSession(FStartSessionRequest Request, const FStartSessionBatchDelegate& SuccessDelegate, const FTDKErrorDelegate& ErrorDelegate)
{
	return false;
}

void TDKLauncherAPI::OnStartSessionBatchResult(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FStartSessionBatchDelegate SuccessDelegate, FTDKErrorDelegate ErrorDelegate)
{

}
