// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKAnalyticsAPI.h"

//#include "Interfaces/IPluginManager.h"

#include "TDKCpp.h"
#include "TDKRuntimeSettings.h"
#include "TDKCommonUtils.h"
#include "TDKAnalyticsConstants.h"

#include "Core/TDKRequestHandler.h"
#include "Core/TDKTimeAPI.h"

#include "Json.h"
#include "JsonUtilities.h"

using namespace TDK;
using namespace AnalyticsModels;

UTDKAnalyticsAPI::UTDKAnalyticsAPI() 
{
	ChainId = -1;
}

UTDKAnalyticsAPI::~UTDKAnalyticsAPI() {}

bool UTDKAnalyticsAPI::TrackCustom(FString EvtName, TMap<FString, FString> EvtProps, bool bHighPriority, const FSendEventBatchDelegate& SuccessDelegate, const FTDKErrorDelegate& ErrorDelegate)
{
	UTDKRuntimeSettings* Settings = GetMutableDefault<UTDKRuntimeSettings>();
	
	FSendEventRequest Request;
	Request.SmartAccountAddress = SmartAccountAddress;
	Request.ChainId = ChainId;
	Request.CartridgeTag = Settings->CartridgeTag;
	Request.SessionId = SessionId;
	Request.EventId = FGuid::NewGuid().ToString(EGuidFormats::Digits);
	Request.TDKVersion = TDKCommon::TDKCommonUtils::GetPluginVersion();
	Request.TdkFlavour = TDKCommon::TDKCommonUtils::GetPluginName();
	Request.EventTimeLocal = ITDKCppModuleInterface::Get().GetTimeAPI()->GetLocalTime();
	// TODO: Save Server Time in Request
	Request.EventName = EvtName;
	Request.EventProps = EvtProps;
	Request.DeviceInfo = TDKCommon::TDKCommonUtils::BuildDeviceInfo();
	Request.AppInfo = TDKCommon::TDKCommonUtils::BuildAppInfo();

	SendEvent(Request, SuccessDelegate, ErrorDelegate);

	return false;
}

bool UTDKAnalyticsAPI::SendEvent(AnalyticsModels::FSendEventRequest Request, const FSendEventBatchDelegate& SuccessDelegate, const FTDKErrorDelegate& ErrorDelegate)
{
	FString AuthValue = Request.AuthenticationContext.IsValid() ? Request.AuthenticationContext->GetApiKey() : GetDefault<UTDKRuntimeSettings>()->ApiKey;

	FString Payload = Request.toJSONString();
	if (Payload.StartsWith(TEXT("{")))
	{
		Payload = TEXT("[") + Payload + TEXT("]");
	}

	FString UrlPath = GetMutableDefault<UTDKRuntimeSettings>()->GetAnalyticsApiUrl();
	UrlPath += "/events";

	auto HttpRequest = TDKRequestHandler::SendRequest(UrlPath, Payload, TEXT("x-api-key"), AuthValue);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UTDKAnalyticsAPI::OnSendEventBatchResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();
}

void UTDKAnalyticsAPI::OnSendEventBatchResult(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FSendEventBatchDelegate SuccessDelegate, FTDKErrorDelegate ErrorDelegate)
{
	//UE_LOG(LogTDKCpp, Warning, TEXT("Request Url: %s"), *HttpRequest->GetURL());
	
	if (HttpResponse == nullptr || !HttpResponse.IsValid())
	{
		ErrorDelegate.ExecuteIfBound(FTDKCppError());
		return;
	}
	
	/*FJsonSerializableArray Headers = HttpRequest->GetAllHeaders();
	for (auto Header : Headers)
	{
		UE_LOG(LogTDKCpp, Warning, TEXT("Header Request: %s"), *Header);
	}*/

	UE_LOG(LogTDKCpp, Warning, TEXT("Response: %s %d"), *HttpResponse->GetContentAsString(), HttpResponse->GetResponseCode());

	AnalyticsModels::FSendEventResponse OutResult;
	FTDKCppError ErrorResult;
	if (TDKRequestHandler::DecodeRequest(HttpRequest, HttpResponse, bSucceeded, OutResult, ErrorResult))
	{
		SuccessDelegate.ExecuteIfBound(OutResult);
	}
	else
	{
		ErrorDelegate.ExecuteIfBound(ErrorResult);
	}
}
