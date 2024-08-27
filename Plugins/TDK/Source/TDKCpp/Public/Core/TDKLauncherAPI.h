// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "Core/TDKLauncherDataModels.h"
#include "Core/TDKError.h"

/**
 * 
 */
namespace TDK
{
	class TDKCPP_API TDKLauncherAPI
	{
	public:
		DECLARE_DELEGATE_OneParam(FStartSessionBatchDelegate, const LauncherModels::FStartSessionResponse&);

		TDKLauncherAPI();
		~TDKLauncherAPI();

		bool StartTDKSession(TDK::LauncherModels::FStartSessionRequest Request, const FStartSessionBatchDelegate& SuccessDelegate = FStartSessionBatchDelegate(), const FTDKErrorDelegate& ErrorDelegate = FTDKErrorDelegate());

	protected:
		void OnStartSessionBatchResult(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FStartSessionBatchDelegate SuccessDelegate, FTDKErrorDelegate ErrorDelegate);
	};
}
