// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKWidgetConnectModal.h"

bool UTDKWidgetConnectModal::IsWalletConnect_Implementation()
{
	return IsConnected;
}

void UTDKWidgetConnectModal::Disconnect_Implementation()
{
	IsConnected = false;
}
