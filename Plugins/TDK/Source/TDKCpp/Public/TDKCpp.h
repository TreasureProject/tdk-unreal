// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTDKCpp, Log, All);

class ITDKCppModuleInterface : public IModuleInterface
{
public:

    /**
    * Singleton-like access to this module's interface.  This is just for convenience!
    * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
    *
    * @return Returns singleton instance, loading the module on demand if needed
    */
    static inline ITDKCppModuleInterface& Get()
    {
        if (IsAvailable())
        {
            return FModuleManager::GetModuleChecked<ITDKCppModuleInterface>("TDKCpp");
        }
        return FModuleManager::LoadModuleChecked<ITDKCppModuleInterface>("TDKCpp");
    }

    /**
    * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
    *
    * @return True if the module is loaded and ready to use
    */
    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded("TDKCpp");
    }
};
