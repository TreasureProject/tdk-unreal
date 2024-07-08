// Fill out your copyright notice in the Description page of Project Settings.


#include "LogActor.h"

#include "Core/TDKAnalyticsAPI.h"

// Sets default values
ALogActor::ALogActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALogActor::BeginPlay()
{
	Super::BeginPlay();

	AnalyticsPtr = ITDKCppModuleInterface::Get().GetAnalyticsAPI();

	TMap<FString, FString> EventProps;
	EventProps.Add(TEXT("step"), TEXT("0"));

	AnalyticsPtr->TrackCustom(TEXT("ftue_started"), EventProps, true, 
		TDK::UTDKAnalyticsAPI::FSendEventBatchDelegate::CreateUObject(this, &ALogActor::OnSuccess),
		TDK::FTDKErrorDelegate::CreateUObject(this, &ALogActor::OnError));
}

// Called every frame
void ALogActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	 
}

void ALogActor::OnSuccess(const TDK::AnalyticsModels::FSendEventResponse& Result) const
{
	UE_LOG(LogTemp, Warning, TEXT("Congratulations, you made your first successful Analytics API call!"));
	UE_LOG(LogTemp, Warning, TEXT("Request Id: %s"), *Result.RequestId);
}

void ALogActor::OnError(const TDK::FTDKCppError& ErrorResult) const
{
	UE_LOG(LogTemp, Error, TEXT("Something went wrong with your first API call.\nHere's some debug information:\n%s"), *ErrorResult.GenerateErrorReport());
}
