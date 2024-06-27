// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Http.h"
#include "Core/TDKCppBaseModel.h"
#include "Core/TDKError.h"

/**
 * 
 */
namespace TDK
{
	class TDKCPP_API TDKRequestHandler
	{
	private:
		static int pendingCalls;
	public:
		static int GetPendingCalls();
		static TSharedRef<IHttpRequest> SendRequest(const FString& urlPath, const FString& callBody, const FString& authKey, const FString& authValue);

		static bool DecodeRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TDK::FTDKCppBaseModel& OutResult, TDK::FTDKCppError& OutError);
		static bool DecodeError(TSharedPtr<FJsonObject> JsonObject, TDK::FTDKCppError& OutError);
	};
}


