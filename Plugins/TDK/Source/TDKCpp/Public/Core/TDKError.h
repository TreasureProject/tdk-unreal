// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
namespace TDK
{
	enum TDKCPP_API TDKErrorCode
	{
        TDKErrorSuccess = 0,
        TDKErrorHostnameNotFound = 1,
        TDKErrorUnkownError = 500,
        TDKErrorConnectionTimeout,
        TDKErrorConnectionRefused,
	};

    struct TDKCPP_API FTDKCppError
    {
        int32 HttpCode;
        FString HttpStatus;
        int32 ErrorCode;
        FString ErrorName;
        FString ErrorMessage;
        TMultiMap< FString, FString > ErrorDetails;

        /*
         * This converts the TDKError into a human readable string describing the error.
         * If error is not found, it will return the http code, status, and error
         */
        FString GenerateErrorReport() const
        {
            FString output = TEXT("");
            if (ErrorMessage.Len() > 0)
            {
                output += ErrorMessage;
            }
            else
            {
                output += "Http Code: ";
                output += FString::FromInt(HttpCode);
                output += "\nHttp Status: ";
                output += HttpStatus;
                output += "\nError Code: ";
                output += FString::FromInt(ErrorCode);
            }
            for (auto& Elem : ErrorDetails)
                output += TEXT(" - ") + Elem.Key + TEXT(": ") + Elem.Value;
            return output;
        }
    };

    DECLARE_DELEGATE_OneParam(FTDKErrorDelegate, const FTDKCppError&);
}
