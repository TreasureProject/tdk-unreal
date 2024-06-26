// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKAnalyticsAPI.h"

#include "Interfaces/IPluginManager.h"
#include "HAL/PlatformMisc.h"
#include "GenericPlatform/GenericPlatformMisc.h"

#include "TDKRuntimeSettings.h"
#include "TDKAnalyticsConstants.h"
#include "Core/TDKRequestHandler.h"

using namespace TDK;
using namespace TDK::AnalyticsModels;

UTDKAnalyticsAPI::UTDKAnalyticsAPI() 
{
	BuildDeviceInfo();

	BuildAppInfo();
}

UTDKAnalyticsAPI::~UTDKAnalyticsAPI() {}

bool TDK::UTDKAnalyticsAPI::TrackCustom(FString EvtName, TMap<FString, FString> EvtProps, bool bHighPriority)
{
	UTDKRuntimeSettings* Settings = GetMutableDefault<UTDKRuntimeSettings>();

	FString Version;
	FString Flavour;
	/*TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("TDK"));
	if (Plugin.IsValid())
	{
		const FPluginDescriptor& Descriptor = Plugin->GetDescriptor();
		Version = Descriptor.VersionName;
		Flavour = Descriptor.ParentPluginName;
	}*/
	
	FTrackCustomRequest Request;
	Request.SmartAccountAddress = SmartAccountAddress;
	Request.ChainId = ChainId;
	Request.CartridgeTag = Settings->CartridgeTag;
	Request.SessionId = SessionId;
	Request.EventId = TEXT("123456");
	Request.TDKVersion = Version;
	Request.TdkFlavour = Flavour;
	Request.EventName = EvtName;
	Request.EventProps = EvtProps;
	Request.DeviceInfo = DeviceInfo;
	Request.AppInfo = AppInfo;

	SendEvent(Request);

	return false;
}

bool TDK::UTDKAnalyticsAPI::SendEvent(TDK::AnalyticsModels::FTrackCustomRequest Request)
{
	return false;
}

void UTDKAnalyticsAPI::BuildDeviceInfo()
{
	FString DeviceName;
	FString DeviceOS;
	FString DeviceId = FGenericPlatformMisc::GetHashedMacAddressString();
	int32 DeviceOSFamily = 0;

#if PLATFORM_WINDOWS
	DeviceName = getenv("COMPUTERNAME");
#else
	DeviceName = getenv("HOSTNAME");
#endif

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

	DeviceOS += TEXT(" ") + FPlatformMisc::GetOSVersion();

	DeviceInfo.DeviceName = DeviceName;
	DeviceInfo.DeviceUniqueId = DeviceId;
	DeviceInfo.DeviceOS = DeviceOS;
	DeviceInfo.DeviceOSFamily = DeviceOSFamily;
	DeviceInfo.DeviceCPU = FPlatformMisc::GetCPUBrand();
}

void UTDKAnalyticsAPI::BuildAppInfo()
{
	FString AppId;
	FString AppVersion;
	bool AppIsEditor;

	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectName"),
		AppId,
		GGameIni
	);

	if (AppId.IsEmpty()) AppId = FApp::GetProjectName();

#if WITH_EDITOR
	AppIsEditor = true;
#else
	AppIsEditor = false;
#endif

	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		AppVersion,
		GGameIni
	);

	AppInfo.AppId = AppId;
	AppInfo.AppIsEditor = AppIsEditor;
	AppInfo.AppVersion = AppVersion;
	AppInfo.AppEnvironment = GetMutableDefault<UTDKRuntimeSettings>()->Env;
}