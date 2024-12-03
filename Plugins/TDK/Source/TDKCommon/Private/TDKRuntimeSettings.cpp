// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKRuntimeSettings.h"

UTDKRuntimeSettings::UTDKRuntimeSettings() :
	CartridgeTag(TEXT("harness")),
	CartridgeName(TEXT("TDK Harness")),
	ProdApiUrl(TEXT("https://tdk-api.treasure.lol")),
	DevApiUrl(TEXT("https://tdk-api.spellcaster.lol")),
	EcosystemId(TEXT("ecosystem.treasure")),
	DevChainId(421614),
	ProdChainId(42161),
	SessionDurationSec(86400),
	SessionMinDurationLeftSec(3600),
	DevAnalyticsApiUrl(TEXT("https://darkmatter.spellcaster.lol/ingress")),
    ProdAnalyticsApiUrl(TEXT("https://darkmatter.treasure.lol/ingress")),
	LauncherApiUrl(TEXT("http://localhost:16001"))
{
	CartridgeIcon = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/TDK/TDK/Texture/Icon/T_Icon_Profile_Logo.T_Icon_Profile_Logo'"));
}

FString UTDKRuntimeSettings::GetAnalyticsApiUrl() const
{
	if (Env == EEnv::DEV)
		return DevAnalyticsApiUrl;
	else
		return ProdAnalyticsApiUrl;
}

FString UTDKRuntimeSettings::GetApiKey() const
{
	if (Env == EEnv::DEV)
		return DevApiKey;
	else
		return ProdApiKey;
}

FString UTDKRuntimeSettings::GetLauncherApiUrl() const
{
	return LauncherApiUrl;
}
