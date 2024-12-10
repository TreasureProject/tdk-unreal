// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDKWidgetConnectModal.generated.h"

/**
 * 
 */
UCLASS()
class TDK_API UTDKWidgetConnectModal : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	bool IsConnected;
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCosmetic, Category = "Status")
	bool IsWalletConnect();

	UFUNCTION(BlueprintNativeEvent, BlueprintCosmetic, Category = "Status")
	void Disconnect();
};
