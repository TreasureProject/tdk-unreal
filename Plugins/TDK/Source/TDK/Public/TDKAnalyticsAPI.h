// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Http.h"
#include "Net/OnlineBlueprintCallProxyBase.h"

#include "TDKAnalyticsModels.h"
#include "TDKJsonObject.h"
#include "TDKAnalyticsAPI.generated.h"

class UTDKJsonObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTDKAnalyticsRequestCompleted, FTDKBaseModel, response, UObject*, customData, bool, successful);

UCLASS(Blueprintable, BlueprintType)
class TDK_API UTDKAnalyticsAPI : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

public:
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateOnFailureTDKError, FTDKError, error, UObject*, customData);

	UPROPERTY(BlueprintAssignable)
	FOnTDKAnalyticsRequestCompleted OnTDKResponse;

	void SetRequestObject(UTDKJsonObject* JsonObject);

	/** Reset saved response data */
	void ResetResponseData();

	virtual void Activate() override;


	DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateOnSuccessSendEvent, FAnalyticsEmptyResult, result, UObject*, customData);

	UFUNCTION(BlueprintCallable, Category = "TDK | Analytics | Events ", meta = (BlueprintInternalUseOnly = "true"))
	static UTDKAnalyticsAPI* SendEvent(FSendEventRequest request, FDelegateOnSuccessSendEvent onSuccess,
		FDelegateOnFailureTDKError onFailure, UObject* customData);

	UFUNCTION(BlueprintCallable, Category = "TDK | Client | Authentication ", meta = (BlueprintInternalUseOnly = "true"))
	void HelperSendEvent(FTDKBaseModel response, UObject* customData, bool successful);


	FString TDKRequestURL;

	bool bIsValidJsonResponse;
	FString ResponseContent;
	int32 ResponseCode;
	UObject* mCustomData;


	FDelegateOnFailureTDKError OnFailure;
	FDelegateOnSuccessSendEvent OnSuccessSendEvent;

private:
	void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

protected:
	/** Contest of Request stored as a String encoded UTF8*/
	FString ReqeustContent;

	/** Internal request data stored as JSON */
	UPROPERTY()
	UTDKJsonObject* RequestJsonObj;

	/** Response data stored as JSON */
	UPROPERTY()
	UTDKJsonObject* ResponseJsonObj;

	/** Mapping of header section to values. Used to generate final header string for request */
	TMap<FString, FString> RequestHeaders;
};
