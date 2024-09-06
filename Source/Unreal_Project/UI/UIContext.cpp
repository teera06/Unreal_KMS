// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIContext.h"
#include "Kismet/GameplayStatics.h"
#include "Global/GlobalHUD.h"
#include "Unreal_Project.h"
// Sets default values for this component's properties
UUIContext::UUIContext()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUIContext::BeginPlay()
{
	Super::BeginPlay();

	// ...
	APlayerController* Con = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	// UI가 입력과 관련이 많기 때문에 HUD를 찾아내려면 
	PlayHUD = Cast<AGlobalHUD>(Con->GetHUD());

	if (nullptr == PlayHUD)
	{
		UE_LOG(MyLog, Error, TEXT("%S(%u)> if (nullptr == TPSPlayHUD)"), __FUNCTION__, __LINE__);
		return;
	}
}


// Called every frame
void UUIContext::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUIContext::UIVisibilitySwitch(EPlayUIType _Type)
{
	if (nullptr == PlayHUD)
	{
		return;
	}

	PlayHUD->UIOn(_Type);
}

void UUIContext::UIVisibilityOn(EPlayUIType _Type)
{
	if (nullptr == PlayHUD)
	{
		return;
	}

	PlayHUD->UIVisibilitySwitch(_Type);
}
