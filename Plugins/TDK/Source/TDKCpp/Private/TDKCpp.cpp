// Copyright Epic Games, Inc. All Rights Reserved.

#include "TDKCpp.h"

#define LOCTEXT_NAMESPACE "FTDKCppModule"

DEFINE_LOG_CATEGORY(LogTDKCpp);

class FTDKCppModule : public ITDKCppModuleInterface
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FTDKCppModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    
}

void FTDKCppModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
    
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTDKCppModule, TDKCpp)