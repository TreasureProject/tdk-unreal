// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TDKCppBaseModel.h"

/**
 * 
 */
namespace TDK
{
	namespace LauncherModels
	{
		struct TDKCPP_API FStartSessionRequest : public FTDKCppRequestCommon
		{
			FStartSessionRequest() :
				FTDKCppRequestCommon()
			{}

			FStartSessionRequest(const FStartSessionRequest& Src) = default;

			FStartSessionRequest(const TSharedPtr<FJsonObject>& Obj) : FStartSessionRequest()
			{
				ReadFromValue(Obj);
			}

			~FStartSessionRequest();

			void WriteJSON(JsonWriter& Writer) const override;
			bool ReadFromValue(const TSharedPtr<FJsonObject>& Obj) override;
		};

		struct TDKCPP_API FStartSessionResponse : public FTDKCppResultCommon
		{
			FStartSessionResponse() :
				FTDKCppResultCommon()
			{}

			FStartSessionResponse(const FStartSessionResponse& src) = default;

			FStartSessionResponse(const TSharedPtr<FJsonObject>& obj) : FStartSessionResponse()
			{
				ReadFromValue(obj);
			}

			~FStartSessionResponse();

			void WriteJSON(JsonWriter& Writer) const override;
			bool ReadFromValue(const TSharedPtr<FJsonObject>& Obj) override;
		};
	}
}