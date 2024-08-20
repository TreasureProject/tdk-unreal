// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TDKCppBaseModel.h"
#include "TDKCommonUtils.h"

/**
 * 
 */

namespace TDK
{
	namespace AnalyticsModels
	{
        struct TDKCPP_API FSendEventRequest : public FTDKCppRequestCommon
		{
            FString SmartAccountAddress;

            int32 ChainId;

            FString CartridgeTag;

            FString EventName;

            FString SessionId;

            FString EventId;

            FString TDKVersion;

            FString TdkFlavour;

            int64 EventTimeLocal;

            int64 EventTimeServer;

            TMap<FString, FString> EventProps;

            TDKCommon::FDeviceInfo DeviceInfo;

            TDKCommon::FAppInfo AppInfo;

            FSendEventRequest() :
                FTDKCppRequestCommon(),
                SmartAccountAddress(),
                ChainId(),
                CartridgeTag(),
                EventName(),
                SessionId(),
                EventId(),
                TDKVersion(),
                TdkFlavour(),
                EventTimeLocal(),
                EventTimeServer(),
                EventProps(),
                DeviceInfo(),
                AppInfo()
            {}

            FSendEventRequest(const FSendEventRequest& Src) = default;

            FSendEventRequest(const TSharedPtr<FJsonObject>& Obj) : FSendEventRequest()
            {
                ReadFromValue(Obj);
            }

            ~FSendEventRequest();

			void WriteJSON(JsonWriter& Writer) const override;
			bool ReadFromValue(const TSharedPtr<FJsonObject>& Obj) override;
		};

        struct TDKCPP_API FEmptyResponse : public TDK::FTDKCppResultCommon
        {
            FEmptyResponse() :
                FTDKCppResultCommon()
            {}

            FEmptyResponse(const FEmptyResponse& src) = default;

            FEmptyResponse(const TSharedPtr<FJsonObject>& obj) : FEmptyResponse()
            {
                ReadFromValue(obj);
            }

            ~FEmptyResponse();

            void WriteJSON(JsonWriter& Writer) const override;
            bool ReadFromValue(const TSharedPtr<FJsonObject>& Obj) override;
        };

        struct TDKCPP_API FSendEventResponse : public TDK::FTDKCppResultCommon
        {
            FString RequestId;

            FString MD5OfMessageAttributes;

            FString MD5OfMessageBody;

            FString MD5OfMessageSystemAttributes;

            FString MessageId;

            FString SequenceNumber;

            FSendEventResponse() :
                FTDKCppResultCommon()
            {}

            FSendEventResponse(const FSendEventResponse& src) = default;

            FSendEventResponse(const TSharedPtr<FJsonObject>& obj) : FSendEventResponse()
            {
                ReadFromValue(obj);
            }

            ~FSendEventResponse();

            void WriteJSON(JsonWriter& Writer) const override;
            bool ReadFromValue(const TSharedPtr<FJsonObject>& Obj) override;
        };
	}
}
