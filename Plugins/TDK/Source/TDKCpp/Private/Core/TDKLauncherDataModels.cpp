// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TDKLauncherDataModels.h"

#include "TDKLauncherConstants.h"

using namespace TDK;
using namespace LauncherModels;

FStartSessionRequest::~FStartSessionRequest()
{

}

void FStartSessionRequest::WriteJSON(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();

	Writer->WriteIdentifierPrefix(TDKCommon::TDKLauncherConstants::Backend_Wallet);
	Writer->WriteValue(BackendWallet);

	Writer->WriteIdentifierPrefix(TDKCommon::TDKLauncherConstants::Approved_Targets);
	
	Writer->WriteArrayStart();

	for(FString ApprovedTarget : ApprovedTargets)
		Writer->WriteValue(ApprovedTarget);

	Writer->WriteArrayEnd();

	Writer->WriteIdentifierPrefix(TDKCommon::TDKLauncherConstants::Native_Token_Limit_Per_Transaction);
	Writer->WriteValue(NativeTokenLimitPerTransaction);

	Writer->WriteIdentifierPrefix(TDKCommon::TDKLauncherConstants::Session_Duration_Sec);
	Writer->WriteValue(SessionDurationSec);

	Writer->WriteIdentifierPrefix(TDKCommon::TDKLauncherConstants::Session_Min_Duration_Left_Sec);
	Writer->WriteValue(SessionMinDurationLeftSec);

	Writer->WriteObjectEnd();
}

bool FStartSessionRequest::ReadFromValue(const TSharedPtr<FJsonObject>& Obj)
{
	return false;
}

FStartSessionResponse::~FStartSessionResponse()
{

}

void FStartSessionResponse::WriteJSON(JsonWriter& Writer) const
{

}

bool FStartSessionResponse::ReadFromValue(const TSharedPtr<FJsonObject>& Obj)
{
	bool HasSucceeded = true;

	const TSharedPtr<FJsonValue> EventNameValue = Obj->TryGetField(TEXT("result"));
	if (EventNameValue.IsValid() && !EventNameValue->IsNull())
	{
		bool TmpValue;
		if (EventNameValue->TryGetBool(TmpValue)) { Result = TmpValue; }
	}

	return HasSucceeded;
}
