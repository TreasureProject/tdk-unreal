// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDKCppBaseModel.h"

/**
 * 
 */

namespace TDK
{
	namespace AnalyticsModels
	{
        struct FDeviceInfo
        {
            FString DeviceName;
            FString DeviceModel;
            int DeviceType;
            FString DeviceUniqueId;
            FString DeviceOS;
            int DeviceOSFamily;
            FString DeviceCPU;
        };

        struct FAppInfo
        {
            FString AppId;
            bool AppIsEditor;
            FString AppVersion;
            int AppEnvironment;
        };
        
        struct TDKCPP_API FTrackCustomRequest : public TDK::FTDKCppBaseModel
		{
            FString SmartAccountAddress;

            int32 ChainId;

            FString CartridgeTag;

            FString EventName;

            FString SessionId;

            FString EventId;

            FString TDKVersion;

            FString TdkFlavour;

            FString EventTimeLocal;

            FString EventTimeServer;

            TMap<FString, FString> EventProps;

            FDeviceInfo DeviceInfo;

            FAppInfo AppInfo;

            FTrackCustomRequest() :
                FTDKCppBaseModel(),
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

            FTrackCustomRequest(const FTrackCustomRequest& Src) = default;

            FTrackCustomRequest(const TSharedPtr<FJsonObject>& Obj) : FTrackCustomRequest()
            {
                ReadFromValue(Obj);
            }

            ~FTrackCustomRequest();

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
	}
}
