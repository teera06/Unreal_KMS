// Fill out your copyright notice in the Description page of Project Settings.


#include "MainActor/MainPlayer.h"
#include "Global/GlobalBlueprintFunctionLibrary.h"

void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	ObjectType = EObjectType::Player;
	UGlobalBlueprintFunctionLibrary::PushActor(GetWorld(), ObjectType, this);
}

void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
