// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKAnalyticsDataModels.h"
#include "TDKCpp.h"
#include "TDKAnalyticsConstants.h"
#include "TDKAnalyticsAPI.h"
#include "TDKRuntimeSettings.h"

TDK::AnalyticsModels::FTrackCustomRequest::~FTrackCustomRequest()
{
    //if (InfoRequestParameters != nullptr) delete InfoRequestParameters;

}

void TDK::AnalyticsModels::FTrackCustomRequest::writeJSON(JsonWriter& writer) const
{
    writer->WriteObjectEnd();
}

bool TDK::AnalyticsModels::FTrackCustomRequest::readFromValue(const TSharedPtr<FJsonObject>& obj)
{
    bool HasSucceeded = true;
    return HasSucceeded;
}
