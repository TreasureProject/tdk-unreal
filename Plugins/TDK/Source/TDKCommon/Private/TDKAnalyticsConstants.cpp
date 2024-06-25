// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKAnalyticsConstants.h"

namespace TDKCommon
{
    // persistent store values
    const FString TDKAnalyticsConstants::PERSISTENT_DIRECTORY_NAME = "AnalyticsStore";

    // properties
    const FString TDKAnalyticsConstants::CARTRIDGE_TAG = "cartridge_tag";
    const FString TDKAnalyticsConstants::PROP_NAME = "name";
    const FString TDKAnalyticsConstants::PROP_ID = "id";
    const FString TDKAnalyticsConstants::PROP_TIME_LOCAL = "time_local";
    const FString TDKAnalyticsConstants::PROP_TIME_SERVER = "time_server";
    const FString TDKAnalyticsConstants::PROP_PROPERTIES = "properties";
    const FString TDKAnalyticsConstants::PROP_DEVICE = "device";
    const FString TDKAnalyticsConstants::PROP_DEVICE_NAME = "device_name";
    const FString TDKAnalyticsConstants::PROP_DEVICE_MODEL = "device_model";
    const FString TDKAnalyticsConstants::PROP_DEVICE_TYPE = "device_type";
    const FString TDKAnalyticsConstants::PROP_DEVICE_UNIQUE_ID = "device_unique_id";
    const FString TDKAnalyticsConstants::PROP_DEVICE_OS = "device_os";
    const FString TDKAnalyticsConstants::PROP_DEVICE_OS_FAMILY = "device_os_family";
    const FString TDKAnalyticsConstants::PROP_DEVICE_CPU = "device_cpu";
    const FString TDKAnalyticsConstants::PROP_APP = "app";
    const FString TDKAnalyticsConstants::PROP_APP_IDENTIFIER = "app_identifier";
    const FString TDKAnalyticsConstants::PROP_APP_IS_EDITOR = "app_is_editor";
    const FString TDKAnalyticsConstants::PROP_APP_VERSION = "app_version";
    const FString TDKAnalyticsConstants::PROP_TDK_FLAVOUR = "tdk_flavour";
    const FString TDKAnalyticsConstants::PROP_TDK_VERSION = "tdk_version";
    const FString TDKAnalyticsConstants::PROP_APP_ENVIRONMENT = "app_environment";
    const FString TDKAnalyticsConstants::PROP_SMART_ACCOUNT = "smart_account";
    const FString TDKAnalyticsConstants::PROP_CHAIN_ID = "chain_id";
    const FString TDKAnalyticsConstants::PROP_TYPE = "type";
    const FString TDKAnalyticsConstants::PROP_SESSION_ID = "session_id";
    const FString TDKAnalyticsConstants::PROP_PERMIT_ADDRESS = "permits_address";
    const FString TDKAnalyticsConstants::PROP_PERMIT_TOKEN_ID = "permits_token_id";
    const FString TDKAnalyticsConstants::PROP_AMOUNT = "amount";
    const FString TDKAnalyticsConstants::PROP_CHARACTERS_ADDRESS = "characters_address";
    const FString TDKAnalyticsConstants::PROP_TOKEN_IDS = "token_ids";
    const FString TDKAnalyticsConstants::PROP_CONTRACT_ADDRESS = "contract_address";
    const FString TDKAnalyticsConstants::PROP_ARGS = "args";
    const FString TDKAnalyticsConstants::PROP_REQUEST_IDS = "request_ids";
    const FString TDKAnalyticsConstants::PROP_ENGINE_TX = "engin_tx";

    // events
    const FString TDKAnalyticsConstants::EVT_APP_START = "app_start";
    const FString TDKAnalyticsConstants::EVT_CONNECT_BTN = "connect_btn";
    const FString TDKAnalyticsConstants::EVT_TREASURECONNECT_CONNECTED = "tc_connected";
    const FString TDKAnalyticsConstants::EVT_TREASURECONNECT_DISCONNECTED = "tc_disconnected";
    const FString TDKAnalyticsConstants::EVT_TREASURECONNECT_OTP_FAILED = "tc_otpfailed";
    const FString TDKAnalyticsConstants::EVT_TREASURECONNECT_UI_LOGIN = "tc_ui_login";
    const FString TDKAnalyticsConstants::EVT_TREASURECONNECT_UI_CONFIRM = "tc_ui_confirm";
    const FString TDKAnalyticsConstants::EVT_TREASURECONNECT_UI_ACCOUNT = "tc_ui_account";

    // events - bridgeworld
    const FString TDKAnalyticsConstants::EVT_BRIDGEWORLD_NFTS_STAKE = "bworld_nfts_stake";
    const FString TDKAnalyticsConstants::EVT_BRIDGEWORLD_NFTS_UNSTAKE = "bworld_nfts_unstake";
    const FString TDKAnalyticsConstants::EVT_BRIDGEWORLD_NFT_STAKE_BATCH = "bworld_nfts_stake_batch";
    const FString TDKAnalyticsConstants::EVT_BRIDGEWORLD_NFT_UNSTAKE_BATCH = "bworld_nfts_unstake_batch";
    const FString TDKAnalyticsConstants::EVT_BRIDGEWORLD_DEPOSIT = "bworld_deposit";
    const FString TDKAnalyticsConstants::EVT_BRIDGEWORLD_WITHDRAW_MAGIC = "bworld_withdraw_magic";
    const FString TDKAnalyticsConstants::EVT_BRIDGEWORLD_WITHDRAW_MAGIC_ALL = "bworld_withdraw_magic_all";
    const FString TDKAnalyticsConstants::EVT_BRIDGEWORLD_REWARDS_CLAIM_MAGIC = "bworld_rewards_claim_magic";
    const FString TDKAnalyticsConstants::EVT_BRIDGEWORLD_CORRUPTION_REMOVAL_START = "bworld_corruption_removal_start";
    const FString TDKAnalyticsConstants::EVT_BRIDGEWORLD_CORRUPTION_REMOVAL_END = "bworld_corruption_removal_end";
}
