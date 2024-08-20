// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "Core/TDKAnalyticsDataModels.h"
#include "Core/TDKError.h"

/**
 * 
 */
namespace TDK
{
	class TDKCPP_API UTDKAnalyticsAPI
	{
	public:
		DECLARE_DELEGATE_OneParam(FSendEventBatchDelegate, const AnalyticsModels::FSendEventResponse&);

		UTDKAnalyticsAPI();
		~UTDKAnalyticsAPI();

		FString GetSessionID() const { return SessionId; }
		FString GetSmartAccountAddress() const { return SmartAccountAddress; }
		int32 GetChainId() const { return ChainId; }

		void SetTreasureConnectInfo(FString Address, int32 Id)
		{
			SmartAccountAddress = Address;
			ChainId = Id;
		}

		bool TrackCustom(FString EvtName, TMap<FString, FString> EvtProps, bool bHighPriority, const FSendEventBatchDelegate& SuccessDelegate = FSendEventBatchDelegate(), const FTDKErrorDelegate& ErrorDelegate = FTDKErrorDelegate());

		// ------------ Generated API calls
		bool SendEvent(TDK::AnalyticsModels::FSendEventRequest Request, const FSendEventBatchDelegate& SuccessDelegate = FSendEventBatchDelegate(), const FTDKErrorDelegate& ErrorDelegate = FTDKErrorDelegate());

	protected:
		// ------------ Generated result handlers
		void OnSendEventBatchResult(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FSendEventBatchDelegate SuccessDelegate, FTDKErrorDelegate ErrorDelegate);


	protected:
		FString SessionId;
		FString SmartAccountAddress;
		int32 ChainId;
	};
}

