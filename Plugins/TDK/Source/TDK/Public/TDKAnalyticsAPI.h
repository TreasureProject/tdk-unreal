// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Http.h"
#include "Net/OnlineBlueprintCallProxyBase.h"

#include "TDKAnalyticsModels.h"
#include "TDKJsonObject.h"
#include "TDKAnalyticsAPI.generated.h"

class UTDKJsonObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTDKAnalyticsRequestCompleted, FTDKBaseModel, Response, bool, Successful);

UCLASS(Blueprintable, BlueprintType)
class TDK_API UTDKAnalyticsAPI : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

public:
	DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateOnFailureTDKError, FTDKError, Error);

	UPROPERTY(BlueprintAssignable)
	FOnTDKAnalyticsRequestCompleted OnTDKResponse;

	/** Set the Request Json object */
	void SetRequestContent(FString ContentString);

	/** Get the Response Json object */
	UTDKJsonObject* GetResponseObject();

	/** Reset saved response data */
	void ResetResponseData();

	/** UOnlineBlueprintCallProxyBase interface */
	virtual void Activate() override;


	//////////////////////////////////////////////////////////////////////////
	// Generated TDK Analytics API Functions
	//////////////////////////////////////////////////////////////////////////

	// callbacks
	DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateOnSuccessSendEvent, FSendEventResult, Result);

	// Send Event API
	static UTDKAnalyticsAPI* TrackCustom(FString EventName, UTDKJsonObject* EventProps, bool bHighPriority, FDelegateOnSuccessSendEvent OnSuccess,
		FDelegateOnFailureTDKError OnFailure);

	UFUNCTION(BlueprintCallable, Category = "TDK | Analytics | Events ", meta = (BlueprintInternalUseOnly = "true"))
	static UTDKAnalyticsAPI* SendEvent(FSendEventRequest Request, FDelegateOnSuccessSendEvent OnSuccess,
		FDelegateOnFailureTDKError OnFailure);

	// // Implements FOnTDKAnalyticsRequestCompleted
	UFUNCTION(BlueprintCallable, Category = "TDK | Client | Authentication ", meta = (BlueprintInternalUseOnly = "true"))
	void HelperSendEvent(FTDKBaseModel Response, bool Successful);


	/** TDK Request Info */
	FString TDKRequestURL;

	/** Is the response valid JSON? */
	bool bIsValidJsonResponse;
	FString ResponseContent;
	int32 ResponseCode;
	UObject* mCustomData;

	FDelegateOnFailureTDKError OnFailure;
	FDelegateOnSuccessSendEvent OnSuccessSendEvent;


private:
	/** Internal bind function for the IHTTPRequest::OnProcessRequestCompleted() event */
	void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

protected:
	/** Contest of Request stored as a String encoded UTF8*/
	FString RequestContent;

	/** Internal request data stored as JSON */
	UPROPERTY()
	UTDKJsonObject* RequestJsonObj;

	/** Response data stored as JSON */
	UPROPERTY()
	UTDKJsonObject* ResponseJsonObj;

	/** Mapping of header section to values. Used to generate final header string for request */
	TMap<FString, FString> RequestHeaders;


	//////////////////////////////////////////////////////////////////////////
	// TDK

	static FString SessionId;

	static FString SmartAccountAddress;

	static int32 ChainId;
};
