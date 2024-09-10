// Fill out your copyright notice in the Description page of Project Settings.


#include "LauncherAPITest.h"

#include "Core/TDKLauncherAPI.h"

// Sets default values
ALauncherAPITest::ALauncherAPITest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALauncherAPITest::BeginPlay()
{
	Super::BeginPlay();

	LauncherPtr = ITDKCppModuleInterface::Get().GetLauncherAPI();

	TDK::LauncherModels::FStartSessionRequest Request;
	LauncherPtr->StartTDKSession(Request, TDK::UTDKLauncherAPI::FStartSessionBatchDelegate::CreateUObject(this, &ALauncherAPITest::OnSuccess),
		TDK::FTDKErrorDelegate::CreateUObject(this, &ALauncherAPITest::OnError));
}

// Called every frame
void ALauncherAPITest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALauncherAPITest::OnSuccess(const TDK::LauncherModels::FStartSessionResponse& Result) const
{
	UE_LOG(LogTemp, Warning, TEXT("Congratulations, you made your first successful Analytics API call!"));

	UE_LOG(LogTemp, Warning, TEXT("Request Result: %s"), Result.Result ? TEXT("true") : TEXT("false"));
}

void ALauncherAPITest::OnError(const TDK::FTDKCppError& ErrorResult) const
{
	UE_LOG(LogTemp, Error, TEXT("Something went wrong with your API call.\nHere's some debug information:\n%s"), *ErrorResult.GenerateErrorReport());
}