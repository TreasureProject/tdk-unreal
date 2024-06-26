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

	AnalyticsPtr->TrackCustom(TEXT("ftue_started"), EventProps, true);
}

// Called every frame
void ALogActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	 
}

