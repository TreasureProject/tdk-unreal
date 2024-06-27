// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TDKCpp.h"
#include "Core/TDKError.h"
#include "Core/TDKAnalyticsDataModels.h"

#include "LogActor.generated.h"

UCLASS()
class TDK_UNREAL_API ALogActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALogActor();

	void OnSuccess(const TDK::AnalyticsModels::FEmptyResponse& Result) const;
	void OnError(const TDK::FTDKCppError& ErrorResult) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TDKAnalyticsPtr AnalyticsPtr;
};
