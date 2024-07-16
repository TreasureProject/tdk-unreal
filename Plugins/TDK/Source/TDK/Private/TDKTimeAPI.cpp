// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKTimeAPI.h"

int64 UTDKTimeAPI::GetLocalTime()
{
    FDateTime Now = FDateTime::UtcNow();

    FDateTime UnixEpoch(1970, 1, 1);
    FTimespan TimespanSinceEpoch = Now - UnixEpoch;

    return FMath::FloorToInt(TimespanSinceEpoch.GetTotalMilliseconds());
}