// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKBlueprintUtils.h"

#include "Runtime/ApplicationCore/Public/HAL/PlatformApplicationMisc.h"

#include <regex>

#include "TDKRuntimeSettings.h"

bool UTDKBlueprintUtils::IsEmailValid(const FString& email)
{
	// define a regular expression
	const std::regex pattern
	("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	// try to match the string with the regular expression
	return std::regex_match(TCHAR_TO_UTF8(*email), pattern);
}

void UTDKBlueprintUtils::CopyText(const FString& text)
{
	FPlatformApplicationMisc::ClipboardCopy(*text);
}

FString UTDKBlueprintUtils::GetCartridgeName()
{
	UTDKRuntimeSettings* Settings = GetMutableDefault<UTDKRuntimeSettings>();
	return Settings->CartridgeName;
}

FString UTDKBlueprintUtils::GetEcosystemPartnerId()
{
	UTDKRuntimeSettings* Settings = GetMutableDefault<UTDKRuntimeSettings>();
	return Settings->EcosystemPartnerId;
}

UTexture2D* UTDKBlueprintUtils::GetCartridgeIcon()
{
	UTDKRuntimeSettings* Settings = GetMutableDefault<UTDKRuntimeSettings>();
	return Settings->CartridgeIcon;
}

FString UTDKBlueprintUtils::GetFactoryAddress()
{
    UTDKRuntimeSettings* Settings = GetMutableDefault<UTDKRuntimeSettings>();
    return Settings->FactoryAddress;
}

int64 UTDKBlueprintUtils::GetChainId()
{
    UTDKRuntimeSettings* Settings = GetMutableDefault<UTDKRuntimeSettings>();
	return Settings->GetChainId();
}
