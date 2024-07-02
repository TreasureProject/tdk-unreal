// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKAnalyticsAPI.h"

UTDKAnalyticsAPI::UTDKAnalyticsAPI(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UTDKAnalyticsAPI::SetRequestObject(UTDKJsonObject* JsonObject)
{
    RequestJsonObj = JsonObject;
}

void UTDKAnalyticsAPI::Activate()
{

}

UTDKAnalyticsAPI* UTDKAnalyticsAPI::SendEvent(FSendEventRequest request, FDelegateOnSuccessSendEvent onSuccess,
	FDelegateOnFailureTDKError onFailure, UObject* customData)
{
    UTDKAnalyticsAPI* manager = NewObject<UTDKAnalyticsAPI>();
    if (manager->IsSafeForRootSet()) manager->AddToRoot();
    UTDKJsonObject* OutRestJsonObj = NewObject<UTDKJsonObject>();
    manager->mCustomData = customData;

    manager->OnSuccessSendEvent = onSuccess;
    manager->OnFailure = onFailure;
    manager->OnTDKResponse.AddDynamic(manager, &UTDKAnalyticsAPI::HelperSendEvent);

    manager->TDKRequestURL = "/events";

    manager->SetRequestObject(OutRestJsonObj);

    return manager;
}

void UTDKAnalyticsAPI::HelperSendEvent(FTDKBaseModel response, UObject* customData, bool successful)
{
}
