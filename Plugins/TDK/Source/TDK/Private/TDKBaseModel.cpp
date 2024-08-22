// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKBaseModel.h"
#include "TDKJsonObject.h"
#include "TDKPrivate.h"

void FTDKError::DecodeError(UTDKJsonObject* ResponseData, int32 ResponseCode)
{
    // Check if we have an error
    if (ResponseCode != 200) // We have an error
    {
        bHasError = true;

        ErrorMessage = ResponseData->GetStringField("message");
    }
    else { bHasError = false; }
}