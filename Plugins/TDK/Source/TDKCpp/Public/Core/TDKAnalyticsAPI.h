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

		void SetTreasureConnectInfo(FString Address, int32 Id)
		{
			SmartAccountAddress = Address;
			ChainId = Id;
		}

		bool TrackCustom(FString EvtName, TMap<FString, FString> EvtProps, bool bHighPriority);

		// APIs
		bool SendEvent(TDK::AnalyticsModels::FTrackCustomRequest Request);

		

	protected:
		TMap<FString, FString> BuildBaseEvent(FString EventName, TMap<FString, FString> EventProps)
		{
			return TMap<FString, FString>();
		}

	protected:
		TMap<FString, FString> DeviceInfo;
		TMap<FString, FString> AppInfo;

		FString SessionId;
		FString SmartAccountAddress;
		int32 ChainId = -1;
	};
}

