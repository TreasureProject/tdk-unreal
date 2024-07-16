// Copyright Epic Games, Inc. All Rights Reserved.

#include "TDKCpp.h"

#include "Core/TDKAnalyticsAPI.h"
#include "Core/TDKTimeAPI.h"

DEFINE_LOG_CATEGORY(LogTDKCpp);

class FTDKCppModule : public ITDKCppModuleInterface
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// Inherited via ITDKCppModuleInterface
	TDKAnalyticsPtr GetAnalyticsAPI() const override { return AnalyticsAPI; }
	TDKTimePtr GetTimeAPI() const override { return TimeAPI; }

	TDKAnalyticsPtr AnalyticsAPI;
	TDKTimePtr TimeAPI;
};

void FTDKCppModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    
	// create the API
	TimeAPI = MakeShareable(new TDK::UTDKTimeAPI());

	AnalyticsAPI = MakeShareable(new TDK::UTDKAnalyticsAPI());
}

void FTDKCppModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
    
}
	
IMPLEMENT_MODULE(FTDKCppModule, TDKCpp)