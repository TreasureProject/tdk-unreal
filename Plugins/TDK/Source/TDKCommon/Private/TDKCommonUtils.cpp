// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKCommonUtils.h"

#include "Misc/Paths.h"
#include "HAL/PlatformMisc.h"
#include "Misc/App.h"
#include "Misc/EngineVersion.h"
#include "Misc/FeedbackContext.h"

#if PLATFORM_ANDROID
#include "Android/AndroidMisc.h"
#elif PLATFORM_IOS
#include "IOS/IOSPlatformMisc.h"
#endif

#include "TDKRuntimeSettings.h"

using namespace TDKCommon;

FDeviceInfo TDKCommonUtils::BuildDeviceInfo()
{
	FString DeviceName;
#if PLATFORM_WINDOWS
	DeviceName = FPlatformMisc::GetEnvironmentVariable(TEXT("COMPUTERNAME"));
#else
	DeviceName = FPlatformMisc::GetEnvironmentVariable(TEXT("HOSTNAME"));
#endif

	FString DeviceOS;
	int32 DeviceOSFamily = 0;
#if PLATFORM_WINDOWS
	DeviceOS = TEXT("Windows");
	DeviceOSFamily = 2;
#elif PLATFORM_MAC
	DeviceOS = TEXT("MacOS");
	DeviceOSFamily = 1;
#elif PLATFORM_LINUX
	DeviceOS = TEXT("Linux");
	DeviceOSFamily = 3;
#elif PLATFORM_ANDROID
	DeviceOS = TEXT("Android");
#elif PLATFORM_IOS
	DeviceOS = TEXT("iOS");
#else
	DeviceOS = TEXT("Unknown");
#endif

	int32 DeviceType = 0;
#if PLATFORM_ANDROID || PLATFORM_IOS
	DeviceType = 1;
#elif PLATFORM_CONSOLE_DYNAMIC_LINK
	DeviceType = 2;
#elif PLATFORM_WINDOWS || PLATFORM_MAC || PLATFORM_LINUX
	DeviceType = 3;
#endif

	DeviceOS += TEXT(" ") + FPlatformMisc::GetOSVersion();

	FDeviceInfo DeviceInfo;
	DeviceInfo.DeviceName = DeviceName;
	DeviceInfo.DeviceType = DeviceType;
	DeviceInfo.DeviceModel = GetDeviceModel();
	DeviceInfo.DeviceUniqueId = FGenericPlatformMisc::GetHashedMacAddressString();
	DeviceInfo.DeviceOS = DeviceOS;
	DeviceInfo.DeviceOSFamily = DeviceOSFamily;
	DeviceInfo.DeviceCPU = FPlatformMisc::GetCPUBrand();

	return DeviceInfo;
}

FAppInfo TDKCommonUtils::BuildAppInfo()
{
	FString AppId;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectName"),
		AppId,
		GGameIni
	);

	if (AppId.IsEmpty()) AppId = FApp::GetProjectName();

	bool AppIsEditor;
#if WITH_EDITOR
	AppIsEditor = true;
#else
	AppIsEditor = false;
#endif

	FString AppVersion;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		AppVersion,
		GGameIni
	);

	FAppInfo AppInfo;

	AppInfo.AppId = AppId;
	AppInfo.AppIsEditor = AppIsEditor;
	AppInfo.AppVersion = AppVersion;
	AppInfo.AppEnvironment = GetMutableDefault<UTDKRuntimeSettings>()->Env;

	return AppInfo;
}

FString TDKCommonUtils::GetDeviceModel()
{
	FString DeviceModel;

#if PLATFORM_WINDOWS
	DeviceModel = "Win Device";
#elif PLATFORM_MAC
	// macOS specific code to get device model (Example: using system commands)
	DeviceModel = "Mac Device"; // Placeholder for macOS-specific implementation
#elif PLATFORM_LINUX
	// Linux specific code to get device model
	DeviceModel = "Linux Device"; // Placeholder for Linux-specific implementation
#elif PLATFORM_ANDROID
	DeviceModel = FAndroidMisc::GetDeviceModel();
#elif PLATFORM_IOS
	DeviceModel = FIOSPlatformMisc::GetDeviceModel();
#else
	DeviceModel = "Unknown Device";
#endif

	return DeviceModel;
}

FString TDKCommonUtils::GetPluginVersion()
{
	return TDKCommonUtils::GetPluginProperty(TEXT("VersionName"));
}

FString TDKCommonUtils::GetPluginName()
{
	return TDKCommonUtils::GetPluginProperty(TEXT("FriendlyName"));
}

FString TDKCommonUtils::GetTDKAuthToken()
{
	FString Token, Param;

	if (FParse::Value(FCommandLine::Get(), TEXT("-tdk-auth-token="), Param))
	{
		Token = Param;
	}

	return Token;
}

FString TDKCommonUtils::GetPluginProperty(FString PropertyName)
{
	// Define the path to the plugin descriptor file
	FString PluginDescriptorFilePath = FPaths::ProjectPluginsDir() / TEXT("TDK/TDK.uplugin");

	FString FileContents;
	if (FFileHelper::LoadFileToString(FileContents, *PluginDescriptorFilePath))
	{
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileContents);

		if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
		{
			FString PropertyValue;
			if (JsonObject->TryGetStringField(PropertyName, PropertyValue))
			{
				return PropertyValue;
			}
		}
	}

	return TEXT("Unknown");
}
