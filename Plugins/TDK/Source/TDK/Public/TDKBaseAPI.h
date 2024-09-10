// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Http.h"
#include "Net/OnlineBlueprintCallProxyBase.h"

#include "TDKJsonObject.h"
#include "TDKBaseModel.h"

#include "TDKBaseAPI.generated.h"

class UTDKJsonObject;
class UTDKAuthenticationContext;

UCLASS(Blueprintable, BlueprintType)
class TDK_API UTDKBaseAPI : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

public:
	void SetCallAuthenticationContext(UTDKAuthenticationContext* InAuthenticationContext);

	/** Set the Request Json object */
	void SetRequestContent(FString ContentString);

	/** Get the Response Json object */
	UTDKJsonObject* GetResponseObject();

	/** Reset saved response data */
	void ResetResponseData();


	/** TDK Request Info */
	FString TDKRequestURL;

	/** Is the response valid JSON? */
	bool bIsValidJsonResponse;
	FString ResponseContent;
	int32 ResponseCode;
	UObject* mCustomData;

protected:
	/** Internal bind function for the IHTTPRequest::OnProcessRequestCompleted() event */
	virtual void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	
	UPROPERTY()
	UTDKAuthenticationContext* CallAuthenticationContext;

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
};
