// Copyright Epic Games, Inc. All Rights Reserved.

#include "TDKPrivate.h"
#include "CoreMinimal.h"

#include "TDKAnalyticsAPI.h"

#define LOCTEXT_NAMESPACE "FTDKModule"

DEFINE_LOG_CATEGORY(LogTDK);
DEFINE_LOG_CATEGORY(LogTDKTests);

class FTDKModule : public ITDK
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FTDKModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    
	UTDKAnalyticsAPI::StaticClass();
}

void FTDKModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
    
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTDKModule, TDK)