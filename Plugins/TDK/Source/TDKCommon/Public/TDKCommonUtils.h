// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

namespace TDKCommon
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

	class TDKCOMMON_API TDKCommonUtils
	{
	public:
        // Device and App Info
		static FDeviceInfo BuildDeviceInfo();
		static FAppInfo BuildAppInfo();
		static FString GetDeviceModel();
	};
}


