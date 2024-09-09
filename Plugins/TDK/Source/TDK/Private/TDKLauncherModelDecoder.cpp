// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKLauncherModelDecoder.h"

#include "TDKJsonObject.h"

FStartSessionResult UTDKLauncherModelDecoder::DecodeStartSessionResponse(UTDKJsonObject* Response)
{
    FStartSessionResult Result;

    Result.Result = !(Response->HasField("result")) ? false : Response->GetBoolField("result");

    return Result;
}

FTDKError UTDKLauncherModelDecoder::DecodeStartSessionError(UTDKJsonObject* Response)
{
    FTDKError Error;

    Error.bHasError = true;
    Error.ErrorMessage = !(Response->HasField("error")) ? TEXT("") : Response->GetStringField("error");

    return Error;
}
