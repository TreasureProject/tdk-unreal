// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TDKRequestHandler.h"

using namespace TDK;

int TDKRequestHandler::pendingCalls = 0;

int TDKRequestHandler::GetPendingCalls()
{
	return 0;
}

TSharedRef<IHttpRequest> TDKRequestHandler::SendRequest(const FString& urlPath, const FString& callBody, const FString& authKey, const FString& authValue)
{
    TDKRequestHandler::pendingCalls += 1;

    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb(TEXT("POST"));
    HttpRequest->SetURL(urlPath);
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
    
    if (authKey != TEXT(""))
        HttpRequest->SetHeader(authKey, authValue);

    HttpRequest->SetContentAsString(callBody);
    return HttpRequest;
}

bool TDKRequestHandler::DecodeRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TDK::FTDKCppBaseModel& OutResult, TDK::FTDKCppError& OutError)
{
    TDKRequestHandler::pendingCalls -= 1;

    FString ResponseStr, ErrorStr;
    if (bSucceeded && HttpResponse.IsValid())
    {
        if (EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
        {
            // Create the Json parser
            ResponseStr = HttpResponse->GetContentAsString();
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create(ResponseStr);

            if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
            {
                if (TDKRequestHandler::DecodeError(JsonObject, OutError))
                {
                    return false;
                }

                const TSharedPtr<FJsonObject>* DataJsonObject;
                if (JsonObject->TryGetObjectField(TEXT("data"), DataJsonObject))
                {
                    return OutResult.ReadFromValue(*DataJsonObject);
                }
            }
        }
        else
        {
            // Create the Json parser
            ResponseStr = HttpResponse->GetContentAsString();
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create(ResponseStr);

            if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
            {
                if (TDKRequestHandler::DecodeError(JsonObject, OutError))
                {
                    return false;
                }
            }
        }
    }

    // If we get here, we failed to connect meaningfully to the server - Assume a timeout
    OutError.HttpCode = 408;
    OutError.ErrorCode = TDKErrorConnectionTimeout;
    // For text returns, use the non-json response if possible, else default to no response
    OutError.ErrorName = OutError.ErrorMessage = OutError.HttpStatus = TEXT("Request Timeout or null response");

    return false;
}

bool TDKRequestHandler::DecodeError(TSharedPtr<FJsonObject> JsonObject, TDK::FTDKCppError& OutError)
{
    // check if returned json indicates an error
    if (JsonObject->HasField(TEXT("errorCode")))
    {
        // deserialize the FPlayFabCppError object 
        JsonObject->TryGetNumberField(TEXT("errorCode"), OutError.ErrorCode);
        JsonObject->TryGetNumberField(TEXT("code"), OutError.HttpCode);
        JsonObject->TryGetStringField(TEXT("status"), OutError.HttpStatus);
        JsonObject->TryGetStringField(TEXT("error"), OutError.ErrorName);
        JsonObject->TryGetStringField(TEXT("errorMessage"), OutError.ErrorMessage);

        const TSharedPtr<FJsonObject>* obj;
        if (JsonObject->TryGetObjectField(TEXT("errorDetails"), obj))
        {
            auto vals = (*obj)->Values;
            for (auto val : vals)
            {
                if (val.Value->AsArray().Num() > 0)
                {
                    for (const auto& item : val.Value->AsArray())
                    {
                        OutError.ErrorDetails.Add(val.Key, item->AsString());
                    }
                }
                else
                {
                    OutError.ErrorDetails.Add(val.Key, val.Value->AsString());
                }
            }
        }

        // TODO: handle global error delegate here

        // We encountered no errors parsing the error
        return true;
    }

    return false;
}
