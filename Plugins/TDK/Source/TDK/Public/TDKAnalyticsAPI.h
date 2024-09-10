// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TDKBaseAPI.h"

#include "TDKAnalyticsModels.h"

#include "TDKAnalyticsAPI.generated.h"

class UTDKJsonObject;
class UTDKAuthenticationContext;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTDKAnalyticsRequestCompleted, FTDKBaseModel, Response, bool, Successful);

UCLASS(Blueprintable, BlueprintType)
class TDK_API UTDKAnalyticsAPI : public UTDKBaseAPI
{
	GENERATED_UCLASS_BODY()

public:
	DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateOnFailureTDKError, FTDKError, Error);

	UPROPERTY(BlueprintAssignable)
		FOnTDKAnalyticsRequestCompleted OnTDKResponse;

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

	// Implements FOnTDKAnalyticsRequestCompleted
	UFUNCTION(BlueprintCallable, Category = "TDK | Analytics | Authentication ", meta = (BlueprintInternalUseOnly = "true"))
	void HelperSendEvent(FTDKBaseModel Response, bool Successful);

	bool bUseApiKey;

	FDelegateOnFailureTDKError OnFailure;
	FDelegateOnSuccessSendEvent OnSuccessSendEvent;
	

protected:
	void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) override;

	//////////////////////////////////////////////////////////////////////////
	// TDK

	static FString SessionId;

	static FString SmartAccountAddress;

	static int32 ChainId;
};
