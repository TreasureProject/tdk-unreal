// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKAnalyticsDataModels.h"
#include "TDKCpp.h"
#include "TDKAnalyticsConstants.h"
#include "TDKAnalyticsAPI.h"

using namespace TDK;
using namespace AnalyticsModels;

FTrackCustomRequest::~FTrackCustomRequest()
{
    //if (InfoRequestParameters != nullptr) delete InfoRequestParameters;

}

void FTrackCustomRequest::WriteJSON(JsonWriter& Writer) const
{
    Writer->WriteObjectStart();

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_SMART_ACCOUNT);
    Writer->WriteValue(SmartAccountAddress);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_CHAIN_ID);
    Writer->WriteValue(ChainId);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::CARTRIDGE_TAG);
    Writer->WriteValue(CartridgeTag);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_NAME);
    Writer->WriteValue(EventName);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_SESSION_ID);
    Writer->WriteValue(SessionId);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_ID);
    Writer->WriteValue(EventId);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_TDK_VERSION);
    Writer->WriteValue(TDKVersion);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_TDK_FLAVOUR);
    Writer->WriteValue(TdkFlavour);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_TIME_LOCAL);
    Writer->WriteValue(EventTimeLocal);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_TIME_SERVER);
    Writer->WriteValue(EventTimeServer);

    WriteMap(Writer, TDKCommon::TDKAnalyticsConstants::PROP_PROPERTIES, EventProps);

    // Device Info
    Writer->WriteObjectStart(TDKCommon::TDKAnalyticsConstants::PROP_DEVICE);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_DEVICE_NAME);
    Writer->WriteValue(DeviceInfo.DeviceName);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_DEVICE_MODEL);
    Writer->WriteValue(DeviceInfo.DeviceModel);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_DEVICE_TYPE);
    Writer->WriteValue(DeviceInfo.DeviceType);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_DEVICE_UNIQUE_ID);
    Writer->WriteValue(DeviceInfo.DeviceUniqueId);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_DEVICE_OS);
    Writer->WriteValue(DeviceInfo.DeviceOS);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_DEVICE_OS_FAMILY);
    Writer->WriteValue(DeviceInfo.DeviceOSFamily);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_DEVICE_CPU);
    Writer->WriteValue(DeviceInfo.DeviceCPU);

    Writer->WriteObjectEnd();

    // App Info
    Writer->WriteObjectStart(TDKCommon::TDKAnalyticsConstants::PROP_APP);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_APP_IDENTIFIER);
    Writer->WriteValue(AppInfo.AppId);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_APP_IS_EDITOR);
    Writer->WriteValue(AppInfo.AppIsEditor);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_APP_VERSION);
    Writer->WriteValue(AppInfo.AppVersion);

    Writer->WriteIdentifierPrefix(TDKCommon::TDKAnalyticsConstants::PROP_APP_ENVIRONMENT);
    Writer->WriteValue(AppInfo.AppEnvironment);

    Writer->WriteObjectEnd();

    Writer->WriteObjectEnd();
}

bool FTrackCustomRequest::ReadFromValue(const TSharedPtr<FJsonObject>& Obj)
{
    bool HasSucceeded = true;

    const TSharedPtr<FJsonValue> EventNameValue = Obj->TryGetField(TEXT("EventName"));
    if (EventNameValue.IsValid() && !EventNameValue->IsNull())
    {
        FString TmpValue;
        if (EventNameValue->TryGetString(TmpValue)) { EventName = TmpValue; }
    }

    const TSharedPtr<FJsonObject>* EventPropsObject;
    if (Obj->TryGetObjectField(TEXT("EventProps"), EventPropsObject))
    {
        for (TMap<FString, TSharedPtr<FJsonValue>>::TConstIterator It((*EventPropsObject)->Values); It; ++It)
        {
            EventProps.Add(It.Key(), It.Value()->AsString());
        }
    }

    return HasSucceeded;
}
