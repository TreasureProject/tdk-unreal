// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

namespace TDKCommon
{
    // Device Information for SendEvent API
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

    // App Information for SendEvent API
    struct FAppInfo
    {
        FString AppId;
        bool AppIsEditor;
        FString AppVersion;
        int AppEnvironment;
    };

	class TDKCOMMON_API TDKCommonUtils
	{
	public:
        // --------- Get Device and App Info
		static FDeviceInfo BuildDeviceInfo();

		static FAppInfo BuildAppInfo();

		static FString GetDeviceModel();

        // --------- Get Self Plugin Boilerplate Information
        static FString GetPluginVersion();

        static FString GetPluginName();

        static FString GetTDKAuthToken();

    protected:
        static FString GetPluginProperty(FString PropertyName);
	};
}


