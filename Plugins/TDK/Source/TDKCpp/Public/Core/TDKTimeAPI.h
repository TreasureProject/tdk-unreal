// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
namespace TDK
{
	class TDKCPP_API UTDKTimeAPI
	{
	public:
		UTDKTimeAPI();
		~UTDKTimeAPI();

		int64 GetLocalTime();
	};
}

