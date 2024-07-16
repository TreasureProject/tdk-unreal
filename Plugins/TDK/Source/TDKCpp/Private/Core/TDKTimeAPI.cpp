// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TDKTimeAPI.h"

using namespace TDK;

UTDKTimeAPI::UTDKTimeAPI()
{
}

UTDKTimeAPI::~UTDKTimeAPI()
{
}

int64 TDK::UTDKTimeAPI::GetLocalTime()
{
    FDateTime Now = FDateTime::UtcNow();

    FDateTime UnixEpoch(1970, 1, 1);
    FTimespan TimespanSinceEpoch = Now - UnixEpoch;

    return (int64) TimespanSinceEpoch.GetTotalMilliseconds();
}
