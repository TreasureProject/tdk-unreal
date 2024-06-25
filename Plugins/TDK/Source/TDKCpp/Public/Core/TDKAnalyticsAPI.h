// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/TDKAnalyticsDataModels.h"

/**
 * 
 */
namespace TDK
{
	class TDKCPP_API UTDKAnalyticsAPI
	{
	public:
		UTDKAnalyticsAPI();
		~UTDKAnalyticsAPI();

		FString GetSessionID() const { return SessionId; }
		FString GetSmartAccountAddress() const { return SmartAccountAddress; }
		int32 GetChainId() const { return ChainId; }

	protected:
		TMap<FString, FString> BuildBaseEvent(FString EventName, TMap<FString, FString> EventProps)
		{

		}

	protected:
		FString SessionId;
		FString SmartAccountAddress;
		int32 ChainId = -1;
	};
}

