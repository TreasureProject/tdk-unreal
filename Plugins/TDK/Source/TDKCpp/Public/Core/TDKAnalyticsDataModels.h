// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDKCppBaseModel.h"

/**
 * 
 */

namespace TDK
{
	namespace AnalyticsModels
	{
		struct TDKCPP_API FTrackCustomRequest : public TDK::FTDKCppBaseModel
		{
            FTrackCustomRequest(const FTrackCustomRequest& src) = default;

            FTrackCustomRequest(const TSharedPtr<FJsonObject>& obj) : FTrackCustomRequest()
            {
                readFromValue(obj);
            }

            ~FTrackCustomRequest();

			void writeJSON(JsonWriter& writer) const override;
			bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
		};
	}
}
