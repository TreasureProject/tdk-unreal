// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKAnalyticsAPI.h"
#include "TDKPrivate.h"
#include "TDKRuntimeSettings.h"

UTDKAnalyticsAPI::UTDKAnalyticsAPI(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UTDKAnalyticsAPI::SetRequestContent(FString ContentString)
{
    RequestContent = ContentString;
}

UTDKJsonObject* UTDKAnalyticsAPI::GetResponseObject()
{
    return ResponseJsonObj;
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
    //FTDKError error = response.responseError;
    //if (error.hasError && OnFailure.IsBound())
    //{
    //    OnFailure.Execute(error, customData);
    //}
    //else if (!error.hasError && OnSuccessLoginWithCustomID.IsBound())
    //{
    //    FClientLoginResult ResultStruct = UTDKClientModelDecoder::decodeLoginResultResponse(response.responseData);
    //    ResultStruct.Request = RequestJsonObj;
    //    // CallAuthenticationContext was set in OnProcessRequestComplete
    //    ResultStruct.AuthenticationContext = CallAuthenticationContext;
    //    OnSuccessSendEvent.Execute(ResultStruct, mCustomData);
    //}   
    //this->RemoveFromRoot();
}

void UTDKAnalyticsAPI::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    // Be sure that we have no data from previous response
    ResetResponseData();

    if (!IsValidLowLevel())
    {
        UE_LOG(LogTDK, Error, TEXT("The request object is invalid during OnProcessRequestComplete."));
        return;
    }
    if (!OnTDKResponse.IsBound())
    {
        UE_LOG(LogTDK, Error, TEXT("OnTDKResponse has come un-bound during OnProcessRequestComplete."));
        return;
    }

    FTDKBaseModel myResponse;

    // Check we have result to process further
    if (!bWasSuccessful)
    {
        UE_LOG(LogTDK, Error, TEXT("Request failed: %s"), *Request->GetURL());

        // Broadcast the result event
        myResponse.responseError.hasError = true;
        myResponse.responseError.ErrorCode = 503;
        myResponse.responseError.ErrorName = "Unable to contact server";
        myResponse.responseError.ErrorMessage = "Unable to contact server";

        OnTDKResponse.Broadcast(myResponse, mCustomData, false);

        return;
    }

    // Save response data as a string
    ResponseContent = Response->GetContentAsString();

    // Save response code as int32
    ResponseCode = Response->GetResponseCode();

    // Try to deserialize data to JSON
    TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ResponseContent);
    FJsonSerializer::Deserialize(JsonReader, ResponseJsonObj->GetRootObject());

    // Decide whether the request was successful
    bIsValidJsonResponse = bWasSuccessful && ResponseJsonObj->GetRootObject().IsValid();

    // Log errors
    if (!bIsValidJsonResponse)
        UE_LOG(LogTDK, Warning, TEXT("JSON could not be decoded!"));

    // Log response state
    UE_LOG(LogTDK, Log, TEXT("Response : %s"), *ResponseContent);

    myResponse.responseError.decodeError(ResponseJsonObj);
    myResponse.responseData = ResponseJsonObj;
    ITDK* pfSettings = &(ITDK::Get());

    // Broadcast the result event
    OnTDKResponse.Broadcast(myResponse, mCustomData, !myResponse.responseError.hasError);
    pfSettings->ModifyPendingCallCount(-1);
}

void UTDKAnalyticsAPI::Activate()
{
    ITDK* pfSettings = &(ITDK::Get());

    FString RequestUrl = GetMutableDefault<UTDKRuntimeSettings>()->GetAnalyticsApiUrl();

    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetURL(RequestUrl);
    HttpRequest->SetVerb(TEXT("POST"));

    // Headers
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
    for (TMap<FString, FString>::TConstIterator It(RequestHeaders); It; ++It)
        HttpRequest->SetHeader(It.Key(), It.Value());

    // Set Json content
    HttpRequest->SetContentAsString(RequestContent);

    UE_LOG(LogTDK, Log, TEXT("Request: %s"), *RequestContent);

    // Bind event
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UTDKAnalyticsAPI::OnProcessRequestComplete);

    // Execute the request
    pfSettings->ModifyPendingCallCount(1);
    HttpRequest->ProcessRequest();
}

void UTDKAnalyticsAPI::ResetResponseData()
{
    if (ResponseJsonObj != nullptr)
        ResponseJsonObj->Reset();
    else
        ResponseJsonObj = NewObject<UTDKJsonObject>();
    bIsValidJsonResponse = false;
}