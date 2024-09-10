// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TDKBaseAPI.h"

#include "TDKLauncherModels.h"

#include "TDKLauncherAPI.generated.h"

class UTDKJsonObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTDKLauncherRequestCompleted, FTDKBaseModel, Response, bool, Successful);

UCLASS(Blueprintable, BlueprintType)
class TDK_API UTDKLauncherAPI : public UTDKBaseAPI
{
	GENERATED_UCLASS_BODY()
	
	
public:
	DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateOnFailureTDKError, FTDKError, Error);

	UPROPERTY(BlueprintAssignable)
		FOnTDKLauncherRequestCompleted OnTDKResponse;

	/** UOnlineBlueprintCallProxyBase interface */
	virtual void Activate() override;


	//////////////////////////////////////////////////////////////////////////
	// Generated TDK Launcher API Functions
	//////////////////////////////////////////////////////////////////////////
	DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateOnSuccessStartSession, FStartSessionResult, Result);

	UFUNCTION(BlueprintCallable, Category = "TDK | Launcher ", meta = (BlueprintInternalUseOnly = "true"))
	static UTDKLauncherAPI* StartSession(FStartSessionRequest Request, FDelegateOnSuccessStartSession OnSuccess,
		FDelegateOnFailureTDKError OnFailure);

	UFUNCTION(BlueprintCallable, Category = "TDK | Launcher ")
	static FString GetAuthToken();

	// Implements FOnTDKLauncherRequestCompleted
	UFUNCTION(BlueprintCallable, Category = "TDK | Launcher | Authentication ", meta = (BlueprintInternalUseOnly = "true"))
	void HelperStartSession(FTDKBaseModel Response, bool Successful);

	FDelegateOnFailureTDKError OnFailure;
	FDelegateOnSuccessStartSession OnSuccessStartSession;

protected:
	void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) override;
};
