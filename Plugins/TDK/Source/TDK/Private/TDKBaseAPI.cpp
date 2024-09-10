// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKBaseAPI.h"


UTDKBaseAPI::UTDKBaseAPI(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
    , CallAuthenticationContext(nullptr)
{
}

void UTDKBaseAPI::SetCallAuthenticationContext(UTDKAuthenticationContext* InAuthenticationContext)
{
    CallAuthenticationContext = InAuthenticationContext;
}

void UTDKBaseAPI::SetRequestContent(FString ContentString)
{
    RequestContent = ContentString;
}

UTDKJsonObject* UTDKBaseAPI::GetResponseObject()
{
    return ResponseJsonObj;
}

void UTDKBaseAPI::ResetResponseData()
{
    if (ResponseJsonObj != nullptr)
        ResponseJsonObj->Reset();
    else
        ResponseJsonObj = NewObject<UTDKJsonObject>();
    bIsValidJsonResponse = false;
}

void UTDKBaseAPI::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    
}