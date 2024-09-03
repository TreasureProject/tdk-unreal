// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKRuntimeSettings.h"

UTDKRuntimeSettings::UTDKRuntimeSettings() :
	CartridgeTag(TEXT("")),
	DevAnalyticsApiUrl(TEXT("")),
	ProdAnalyticsApiUrl(TEXT("")),
	ApiKey(TEXT("")),
	LauncherApiUrl(TEXT("http://localhost:16001"))
{

}

FString UTDKRuntimeSettings::GetAnalyticsApiUrl() const
{
	if (Env == EEnv::DEV)
		return DevAnalyticsApiUrl;
	else
		return ProdAnalyticsApiUrl;
}

FString UTDKRuntimeSettings::GetLauncherApiUrl() const
{
	return LauncherApiUrl;
}
