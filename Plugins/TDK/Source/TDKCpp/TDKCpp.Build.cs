// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO; 

public class TDKCpp : ModuleRules
{
    public TDKCpp(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
      
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));

        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public/Core"));

        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Core"));

        PublicDependencyModuleNames.AddRange(new string[]{
            "Core",
            "CoreUObject",
            "HTTP",
            "Json",
            "JsonUtilities",
            "TDKCommon"
        });
    }
}