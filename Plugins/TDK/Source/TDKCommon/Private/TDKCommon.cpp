// Copyright Epic Games, Inc. All Rights Reserved.

#include "TDKCommon.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#endif // WITH_EDITOR

#include "TDKRuntimeSettings.h"

#define LOCTEXT_NAMESPACE "FTDKCommonModule"

DEFINE_LOG_CATEGORY(LogTDKCommon);

class FTDKCommonModule : public ITDKCommonModuleInterface
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// Settings
	void RegisterSettings();
	void UnregisterSettings();
};

void FTDKCommonModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    RegisterSettings();
}

void FTDKCommonModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
    UnregisterSettings();
}

void FTDKCommonModule::RegisterSettings()
{
#if WITH_EDITOR
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "TDK",
            LOCTEXT("TDKSettingsName", "TDK"),
            LOCTEXT("TDKSettingsDescription", "Configure the TDK plugin"),
            GetMutableDefault<UTDKRuntimeSettings>()
        );
    }
#endif // WITH_EDITOR
}

void FTDKCommonModule::UnregisterSettings()
{
#if WITH_EDITOR
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->UnregisterSettings("Project", "Plugins", "TDK");
    }
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTDKCommonModule, TDKCommon)