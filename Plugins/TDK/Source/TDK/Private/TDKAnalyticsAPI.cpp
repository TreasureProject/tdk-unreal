// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKAnalyticsAPI.h"

#include "TDKPrivate.h"
#include "TDKRuntimeSettings.h"
#include "TDKCommonUtils.h"
#include "TDKAnalyticsConstants.h"
#include "TDKTimeAPI.h"
#include "TDKAnalyticsModels.h"
#include "TDKAnalyticsModelDecoder.h"

FString UTDKAnalyticsAPI::SessionId = TEXT("");

FString UTDKAnalyticsAPI::SmartAccountAddress = TEXT("");

int32 UTDKAnalyticsAPI::ChainId = -1;

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

UTDKAnalyticsAPI* UTDKAnalyticsAPI::TrackCustom(FString EventName, UTDKJsonObject* EventProps, bool bHighPriority, FDelegateOnSuccessSendEvent OnSuccess, FDelegateOnFailureTDKError OnFailure)
{
    FSendEventRequest Request;

    Request.EventName = EventName;
    Request.EventProps = EventProps;

    return UTDKAnalyticsAPI::SendEvent(Request, OnSuccess, OnFailure);
}

UTDKAnalyticsAPI* UTDKAnalyticsAPI::SendEvent(FSendEventRequest Request, FDelegateOnSuccessSendEvent OnSuccess,
	FDelegateOnFailureTDKError OnFailure)
{
    UTDKAnalyticsAPI* Manager = NewObject<UTDKAnalyticsAPI>();
    if (Manager->IsSafeForRootSet()) Manager->AddToRoot();
    UTDKJsonObject* OutRestJsonObj = NewObject<UTDKJsonObject>();

    Manager->OnSuccessSendEvent = OnSuccess;
    Manager->OnFailure = OnFailure;
    Manager->OnTDKResponse.AddDynamic(Manager, &UTDKAnalyticsAPI::HelperSendEvent);

    Manager->TDKRequestURL = "/events";

    UTDKRuntimeSettings* Settings = GetMutableDefault<UTDKRuntimeSettings>();

    // Serialize all the request properties to json
    OutRestJsonObj->SetStringField(TDKCommon::TDKAnalyticsConstants::PROP_SMART_ACCOUNT, SmartAccountAddress);
    OutRestJsonObj->SetIntegerField(TDKCommon::TDKAnalyticsConstants::PROP_CHAIN_ID, ChainId);
    OutRestJsonObj->SetStringField(TDKCommon::TDKAnalyticsConstants::CARTRIDGE_TAG, Settings->CartridgeTag);
    OutRestJsonObj->SetStringField(TDKCommon::TDKAnalyticsConstants::PROP_NAME, Request.EventName);
    OutRestJsonObj->SetStringField(TDKCommon::TDKAnalyticsConstants::PROP_SESSION_ID, SessionId);
    OutRestJsonObj->SetStringField(TDKCommon::TDKAnalyticsConstants::PROP_ID, FGuid::NewGuid().ToString(EGuidFormats::Digits));
    OutRestJsonObj->SetStringField(TDKCommon::TDKAnalyticsConstants::PROP_TDK_VERSION, TDKCommon::TDKCommonUtils::GetPluginVersion());
    OutRestJsonObj->SetStringField(TDKCommon::TDKAnalyticsConstants::PROP_TDK_FLAVOUR, TDKCommon::TDKCommonUtils::GetPluginName());
    OutRestJsonObj->SetBigIntegerField(TDKCommon::TDKAnalyticsConstants::PROP_TIME_LOCAL, UTDKTimeAPI::GetLocalTime());
    // TODO: Save Server Time in Json
    OutRestJsonObj->SetBigIntegerField(TDKCommon::TDKAnalyticsConstants::PROP_TIME_SERVER, UTDKTimeAPI::GetLocalTime());

    OutRestJsonObj->SetObjectField(TDKCommon::TDKAnalyticsConstants::PROP_PROPERTIES, Request.EventProps);

    TDKCommon::FDeviceInfo DeviceInfo = TDKCommon::TDKCommonUtils::BuildDeviceInfo();
    UTDKJsonObject* DeviceInfoJsonObj = NewObject<UTDKJsonObject>();
    DeviceInfoJsonObj->SetStringField(TDKCommon::TDKAnalyticsConstants::PROP_DEVICE_NAME, DeviceInfo.DeviceName);
    DeviceInfoJsonObj->SetStringField(TDKCommon::TDKAnalyticsConstants::PROP_DEVICE_MODEL, DeviceInfo.DeviceModel);
    DeviceInfoJsonObj->SetIntegerField(TDKCommon::TDKAnalyticsConstants::PROP_DEVICE_TYPE, DeviceInfo.DeviceType);
    DeviceInfoJsonObj->SetStringField(TDKCommon::TDKAnalyticsConstants::PROP_DEVICE_UNIQUE_ID, DeviceInfo.DeviceUniqueId);
    DeviceInfoJsonObj->SetStringField(TDKCommon::TDKAnalyticsConstants::PROP_DEVICE_OS, DeviceInfo.DeviceOS);
    DeviceInfoJsonObj->SetIntegerField(TDKCommon::TDKAnalyticsConstants::PROP_DEVICE_OS_FAMILY, DeviceInfo.DeviceOSFamily);
    DeviceInfoJsonObj->SetStringField(TDKCommon::TDKAnalyticsConstants::PROP_DEVICE_CPU, DeviceInfo.DeviceCPU);

    OutRestJsonObj->SetObjectField(TDKCommon::TDKAnalyticsConstants::PROP_DEVICE, DeviceInfoJsonObj);

    TDKCommon::FAppInfo AppInfo = TDKCommon::TDKCommonUtils::BuildAppInfo();
    UTDKJsonObject* AppInfoJsonObj = NewObject<UTDKJsonObject>();
    AppInfoJsonObj->SetStringField(TDKCommon::TDKAnalyticsConstants::PROP_APP_IDENTIFIER, AppInfo.AppId);
    AppInfoJsonObj->SetBoolField(TDKCommon::TDKAnalyticsConstants::PROP_APP_IS_EDITOR, AppInfo.AppIsEditor);
    AppInfoJsonObj->SetStringField(TDKCommon::TDKAnalyticsConstants::PROP_APP_VERSION, AppInfo.AppVersion);
    AppInfoJsonObj->SetIntegerField(TDKCommon::TDKAnalyticsConstants::PROP_APP_ENVIRONMENT, AppInfo.AppEnvironment);

    OutRestJsonObj->SetObjectField(TDKCommon::TDKAnalyticsConstants::PROP_APP, AppInfoJsonObj);

    // Serialize data to json string
    FString OutputString;
    TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
    FJsonSerializer::Serialize(OutRestJsonObj->GetRootObject().ToSharedRef(), Writer);

    if (OutputString.StartsWith(TEXT("{")))
    {
        OutputString = TEXT("[") + OutputString + TEXT("]");
    }

    Manager->SetRequestContent(OutputString);

    return Manager;
}

void UTDKAnalyticsAPI::HelperSendEvent(FTDKBaseModel Response, bool Successful)
{
    FTDKError Error = Response.ResponseError;
    if (Error.bHasError && OnFailure.IsBound())
    {
        OnFailure.Execute(Error);
    }
    else if (!Error.bHasError && OnSuccessSendEvent.IsBound())
    {
        FSendEventResult ResultStruct = UTDKAnalyticsModelDecoder::DecodeSendEventResponse(Response.ResponseData);
        ResultStruct.Request = RequestJsonObj;

        OnSuccessSendEvent.Execute(ResultStruct);
    }   
    this->RemoveFromRoot();
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

void UTDKAnalyticsAPI::Activate()
{
    ITDK* pfSettings = &(ITDK::Get());

    FString RequestUrl = GetMutableDefault<UTDKRuntimeSettings>()->GetAnalyticsApiUrl() + TDKRequestURL;

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