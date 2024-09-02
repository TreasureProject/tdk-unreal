// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKLauncherModelDecoder.h"

#include "TDKJsonObject.h"

FStartSessionResult UTDKLauncherModelDecoder::DecodeStartSessionResponse(UTDKJsonObject* Response)
{
    FStartSessionResult Result;

    Result.Result = !(Response->HasField("result")) ? false : Response->GetBoolField("result");

    return Result;
}
