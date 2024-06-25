// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKAnalyticsDataModels.h"
#include "TDKCpp.h"
#include "TDKAnalyticsConstants.h"
#include "TDKAnalyticsAPI.h"

TDK::AnalyticsModels::FTrackCustomRequest::~FTrackCustomRequest()
{
    //if (InfoRequestParameters != nullptr) delete InfoRequestParameters;

}

void TDK::AnalyticsModels::FTrackCustomRequest::WriteJSON(JsonWriter& Writer) const
{
    TDKAnalyticsPtr AnalyticsAPI = ITDKCppModuleInterface::Get().GetAnalyticsAPI();

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

    WriteMap(Writer, TDKCommon::TDKAnalyticsConstants::PROP_DEVICE, DeviceInfo);

    WriteMap(Writer, TDKCommon::TDKAnalyticsConstants::PROP_APP, AppInfo);

    Writer->WriteObjectEnd();
}

bool TDK::AnalyticsModels::FTrackCustomRequest::ReadFromValue(const TSharedPtr<FJsonObject>& Obj)
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
