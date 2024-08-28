// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TDKLauncherAPI.h"

#include "TDKCpp.h"

#include "Core/TDKRequestHandler.h"

using namespace TDK;
using namespace LauncherModels;

UTDKLauncherAPI::UTDKLauncherAPI()
{
}

UTDKLauncherAPI::~UTDKLauncherAPI()
{
}

bool UTDKLauncherAPI::StartTDKSession(FStartSessionRequest Request, const FStartSessionBatchDelegate& SuccessDelegate, const FTDKErrorDelegate& ErrorDelegate)
{
	FString UrlPath = GetMutableDefault<UTDKRuntimeSettings>()->GetLauncherApiUrl();
	UrlPath += "/tdk-start-session";

	auto HttpRequest = TDKRequestHandler::SendRequest(UrlPath, Request.toJSONString(), TEXT(""), TEXT(""));
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UTDKLauncherAPI::OnStartSessionBatchResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();
}

void UTDKLauncherAPI::OnStartSessionBatchResult(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FStartSessionBatchDelegate SuccessDelegate, FTDKErrorDelegate ErrorDelegate)
{
	UE_LOG(LogTDKCpp, Warning, TEXT("Response: %s %d"), *HttpResponse->GetContentAsString(), HttpResponse->GetResponseCode());

	LauncherModels::FStartSessionResponse OutResult;
	FTDKCppError ErrorResult;
	if (TDKRequestHandler::DecodeRequest(HttpRequest, HttpResponse, bSucceeded, OutResult, ErrorResult))
	{
		SuccessDelegate.ExecuteIfBound(OutResult);
	}
	else
	{
		ErrorDelegate.ExecuteIfBound(ErrorResult);
	}
}
