// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKLauncherAPI.h"

#include "TDKPrivate.h"
#include "TDKLauncherConstants.h"
#include "TDKLauncherModelDecoder.h"

UTDKLauncherAPI::UTDKLauncherAPI(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UTDKLauncherAPI::Activate()
{
    ITDK* pfSettings = &(ITDK::Get());

    FString RequestUrl = GetMutableDefault<UTDKRuntimeSettings>()->GetLauncherApiUrl() + TDKRequestURL;

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
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UTDKLauncherAPI::OnProcessRequestComplete);

    // Execute the request
    pfSettings->ModifyPendingCallCount(1);
    HttpRequest->ProcessRequest();
}

UTDKLauncherAPI* UTDKLauncherAPI::StartSession(FStartSessionRequest Request, FDelegateOnSuccessStartSession OnSuccess, FDelegateOnFailureTDKError OnFailure)
{
    // Objects containing request data
    UTDKLauncherAPI* Manager = NewObject<UTDKLauncherAPI>();
    if (Manager->IsSafeForRootSet()) Manager->AddToRoot();
    UTDKJsonObject* OutRestJsonObj = NewObject<UTDKJsonObject>();

    // Assign delegates
    Manager->OnSuccessStartSession = OnSuccess;
    Manager->OnFailure = OnFailure;
    Manager->OnTDKResponse.AddDynamic(Manager, &UTDKLauncherAPI::HelperStartSession);

    // Setup the request
    Manager->TDKRequestURL = "/tdk-start-session";

    // Serialize all the request properties to json
    OutRestJsonObj->SetStringField(TDKCommon::TDKLauncherConstants::Backend_Wallet, Request.BackendWallet);
    OutRestJsonObj->SetStringArrayField(TDKCommon::TDKLauncherConstants::Approved_Targets, Request.ApprovedTargets);
    OutRestJsonObj->SetBigIntegerField(TDKCommon::TDKLauncherConstants::Native_Token_Limit_Per_Transaction, Request.NativeTokenLimitPerTransaction);
    OutRestJsonObj->SetIntegerField(TDKCommon::TDKLauncherConstants::Session_Duration_Sec, Request.SessionDurationSec);
    OutRestJsonObj->SetIntegerField(TDKCommon::TDKLauncherConstants::Session_Min_Duration_Left_Sec, Request.SessionMinDurationLeftSec);

    // Serialize data to json string
    FString OutputString;
    TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
    FJsonSerializer::Serialize(OutRestJsonObj->GetRootObject().ToSharedRef(), Writer);

    Manager->SetRequestContent(OutputString);

    return Manager;
}

void UTDKLauncherAPI::HelperStartSession(FTDKBaseModel Response, bool Successful)
{
    FTDKError Error = Response.ResponseError;
    if (Error.bHasError && OnFailure.IsBound())
    {
        OnFailure.Execute(Error);
    }
    else if (!Error.bHasError && OnSuccessStartSession.IsBound())
    {
        FStartSessionResult ResultStruct = UTDKLauncherModelDecoder::DecodeStartSessionResponse(Response.ResponseData);
        ResultStruct.Request = RequestJsonObj;

        OnSuccessStartSession.Execute(ResultStruct);
    }
    this->RemoveFromRoot();
}

void UTDKLauncherAPI::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
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

    FTDKBaseModel ResponseModel;

    // Check we have result to process further
    if (!bWasSuccessful)
    {
        UE_LOG(LogTDK, Error, TEXT("Request failed: %s"), *Request->GetURL());

        // Broadcast the result event
        ResponseModel.ResponseError.bHasError = true;
        ResponseModel.ResponseError.ErrorCode = 503;
        ResponseModel.ResponseError.ErrorName = "Unable to contact server";
        ResponseModel.ResponseError.ErrorMessage = "Unable to contact server";

        OnTDKResponse.Broadcast(ResponseModel, false);

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
    UE_LOG(LogTDK, Log, TEXT("Response Content: %s"), *ResponseContent);
    UE_LOG(LogTDK, Log, TEXT("Response Code: %d"), ResponseCode);

    ResponseModel.ResponseError.DecodeError(ResponseJsonObj, ResponseCode);
    ResponseModel.ResponseData = ResponseJsonObj;
    ITDK* pfSettings = &(ITDK::Get());

    // Broadcast the result event
    OnTDKResponse.Broadcast(ResponseModel, !ResponseModel.ResponseError.bHasError);
    pfSettings->ModifyPendingCallCount(-1);
}