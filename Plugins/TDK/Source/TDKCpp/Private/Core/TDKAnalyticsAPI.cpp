// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKAnalyticsAPI.h"

#include "Interfaces/IPluginManager.h"

#include "TDKRuntimeSettings.h"

using namespace TDK;
using namespace TDK::AnalyticsModels;

UTDKAnalyticsAPI::UTDKAnalyticsAPI() {}

UTDKAnalyticsAPI::~UTDKAnalyticsAPI() {}

bool TDK::UTDKAnalyticsAPI::TrackCustom(FString EvtName, TMap<FString, FString> EvtProps, bool bHighPriority)
{
	UTDKRuntimeSettings* Settings = GetMutableDefault<UTDKRuntimeSettings>();

	FString Version;
	FString Flavour;
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("TDK"));
	if (Plugin.IsValid())
	{
		const FPluginDescriptor& Descriptor = Plugin->GetDescriptor();
		Version = Descriptor.VersionName;
		Flavour = Descriptor.ParentPluginName;
	}
	
	TDK::AnalyticsModels::FTrackCustomRequest Request;
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
}

bool TDK::UTDKAnalyticsAPI::SendEvent(TDK::AnalyticsModels::FTrackCustomRequest Request)
{
	return false;
}
