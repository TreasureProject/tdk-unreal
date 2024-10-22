// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKRuntimeSettings.h"

UTDKRuntimeSettings::UTDKRuntimeSettings() :
	CartridgeTag(TEXT("harness")),
	CartridgeName(TEXT("TDK Harness")),
	DevAnalyticsApiUrl(TEXT("https://darkmatter.spellcaster.lol/ingress")),
	ProdAnalyticsApiUrl(TEXT("https://darkmatter.treasure.lol/ingress")),
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
