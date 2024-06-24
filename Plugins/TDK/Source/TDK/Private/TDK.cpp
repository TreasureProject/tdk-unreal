// Copyright Epic Games, Inc. All Rights Reserved.

#include "TDK.h"

#define LOCTEXT_NAMESPACE "FTDKModule"

DEFINE_LOG_CATEGORY(LogTDK);

class FTDKModule : public ITDKModuleInterface
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FTDKModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    
}

void FTDKModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
    
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTDKModule, TDK)