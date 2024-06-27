// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKAnalyticsAPI.h"

#include "Interfaces/IPluginManager.h"

#include "TDKCpp.h"
#include "TDKRuntimeSettings.h"
#include "TDKCommonUtils.h"
#include "TDKAnalyticsConstants.h"

#include "Core/TDKRequestHandler.h"
#include "TDKAnalyticsAPI.h"

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

	FString Version;
	FString Flavour;
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("TDK"));
	if (Plugin.IsValid())
	{
		const FPluginDescriptor& Descriptor = Plugin->GetDescriptor();
		Version = Descriptor.VersionName;
		Flavour = Descriptor.ParentPluginName;
	}
	
	FTrackCustomRequest Request;
	Request.SmartAccountAddress = SmartAccountAddress;
	Request.ChainId = ChainId;
	Request.CartridgeTag = Settings->CartridgeTag;
	Request.SessionId = SessionId;
	Request.EventId = TEXT("123456");
	Request.TDKVersion = Version;
	Request.TdkFlavour = Flavour;
	Request.EventName = EvtName;
	Request.EventProps = EvtProps;
	Request.DeviceInfo = TDKCommon::TDKCommonUtils::BuildDeviceInfo();
	Request.AppInfo = TDKCommon::TDKCommonUtils::BuildAppInfo();

	SendEvent(Request, SuccessDelegate, ErrorDelegate);

	return false;
}

bool UTDKAnalyticsAPI::SendEvent(AnalyticsModels::FTrackCustomRequest Request, const FSendEventBatchDelegate& SuccessDelegate, const FTDKErrorDelegate& ErrorDelegate)
{
	UE_LOG(LogTDKCpp, Warning, TEXT("%s"), *Request.toJSONString());

	return SendEventBatch(Request.toJSONString(), SuccessDelegate, ErrorDelegate);
}

bool TDK::UTDKAnalyticsAPI::SendEventBatch(FString Payload, const FSendEventBatchDelegate& SuccessDelegate, const FTDKErrorDelegate& ErrorDelegate)
{
	if (Payload.StartsWith(TEXT("{")))
	{
		Payload = TEXT("[") + Payload + TEXT("]");
	}

	FString UrlPath = GetMutableDefault<UTDKRuntimeSettings>()->GetAnalyticsApiUrl();
	UrlPath += "/events";

	auto HttpRequest = TDKRequestHandler::SendRequest(UrlPath, Payload, TEXT(""), TEXT(""));
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UTDKAnalyticsAPI::OnSendEventBatchResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();
}

void UTDKAnalyticsAPI::OnSendEventBatchResult(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FSendEventBatchDelegate SuccessDelegate, FTDKErrorDelegate ErrorDelegate)
{
	AnalyticsModels::FEmptyResponse outResult;
	FTDKCppError errorResult;
	if (TDKRequestHandler::DecodeRequest(HttpRequest, HttpResponse, bSucceeded, outResult, errorResult))
	{
		SuccessDelegate.ExecuteIfBound(outResult);
	}
	else
	{
		ErrorDelegate.ExecuteIfBound(errorResult);
	}
}
