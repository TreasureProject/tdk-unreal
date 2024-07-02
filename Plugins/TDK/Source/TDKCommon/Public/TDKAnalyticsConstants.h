// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

namespace TDKCommon
{
	class TDKCOMMON_API TDKAnalyticsConstants
	{
	public:
        // -------- event cache values
        static const int MAX_CACHE_EVENT_COUNT = 10;
        static const int MAX_CACHE_SIZE_KB = 64;
        static const int CACHE_FLUSH_TIME_SECONDS = 10;

        // -------- persistent store values
        static const FString PERSISTENT_DIRECTORY_NAME;
        static const int PERSISTENT_MAX_RETRIES = 5;

        // -------- properties
        static const FString CARTRIDGE_TAG;
        static const FString PROP_NAME;
        static const FString PROP_ID;
        static const FString PROP_TIME_LOCAL;
        static const FString PROP_TIME_SERVER;
        static const FString PROP_PROPERTIES;
        static const FString PROP_DEVICE;
        static const FString PROP_DEVICE_NAME;
        static const FString PROP_DEVICE_MODEL;
        static const FString PROP_DEVICE_TYPE;
        static const FString PROP_DEVICE_UNIQUE_ID;
        static const FString PROP_DEVICE_OS;
        static const FString PROP_DEVICE_OS_FAMILY;
        static const FString PROP_DEVICE_CPU;
        static const FString PROP_APP;
        static const FString PROP_APP_IDENTIFIER;
        static const FString PROP_APP_IS_EDITOR;
        static const FString PROP_APP_VERSION;
        static const FString PROP_TDK_FLAVOUR;
        static const FString PROP_TDK_VERSION;
        static const FString PROP_APP_ENVIRONMENT;
        static const FString PROP_SMART_ACCOUNT;
        static const FString PROP_CHAIN_ID;
        static const FString PROP_TYPE;
        static const FString PROP_SESSION_ID;
        static const FString PROP_PERMIT_ADDRESS;
        static const FString PROP_PERMIT_TOKEN_ID;
        static const FString PROP_AMOUNT;
        static const FString PROP_CHARACTERS_ADDRESS;
        static const FString PROP_TOKEN_IDS;
        static const FString PROP_CONTRACT_ADDRESS;
        static const FString PROP_ARGS;
        static const FString PROP_REQUEST_IDS;
        static const FString PROP_ENGINE_TX;

        // -------- events
        static const FString EVT_APP_START;
        static const FString EVT_CONNECT_BTN;
        static const FString EVT_TREASURECONNECT_CONNECTED;
        static const FString EVT_TREASURECONNECT_DISCONNECTED;
        static const FString EVT_TREASURECONNECT_OTP_FAILED;
        static const FString EVT_TREASURECONNECT_UI_LOGIN;
        static const FString EVT_TREASURECONNECT_UI_CONFIRM;
        static const FString EVT_TREASURECONNECT_UI_ACCOUNT;

        // -------- events - bridgeworld
        static const FString EVT_BRIDGEWORLD_NFTS_STAKE;
        static const FString EVT_BRIDGEWORLD_NFTS_UNSTAKE;
        static const FString EVT_BRIDGEWORLD_NFT_STAKE_BATCH;
        static const FString EVT_BRIDGEWORLD_NFT_UNSTAKE_BATCH;
        static const FString EVT_BRIDGEWORLD_DEPOSIT;
        static const FString EVT_BRIDGEWORLD_WITHDRAW_MAGIC;
        static const FString EVT_BRIDGEWORLD_WITHDRAW_MAGIC_ALL;
        static const FString EVT_BRIDGEWORLD_REWARDS_CLAIM_MAGIC;
        static const FString EVT_BRIDGEWORLD_CORRUPTION_REMOVAL_START;
        static const FString EVT_BRIDGEWORLD_CORRUPTION_REMOVAL_END;
	};
}


