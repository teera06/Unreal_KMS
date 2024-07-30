// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GlobalBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Global/GlobalHUD.h"
#include "Global/GlobalGameInstance.h"
#include "Unreal_Project.h"

#if WITH_EDITOR
void UGlobalBlueprintFunctionLibrary::DebugTextPrint(UWorld* _World, FString Text)
{

	APlayerController* Con = UGameplayStatics::GetPlayerController(_World, 0);
	// UI가 입력과 관련이 많기 때문에 HUD를 찾아내려면 
	AGlobalHUD* Global = Cast<AGlobalHUD>(Con->GetHUD());

	if (nullptr == Global)
	{
		return;
	}

	Global->AddDebugString(Text);
}

#endif
AGlobalHUD* UGlobalBlueprintFunctionLibrary::GetGlobalHUD(const UObject* WorldContextObject)
{
	APlayerController* Con = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	// UI가 입력과 관련이 많기 때문에 HUD를 찾아내려면 
	AGlobalHUD* Hud = Cast<AGlobalHUD>(Con->GetHUD());

	return Hud;
}

UGlobalGameInstance* UGlobalBlueprintFunctionLibrary::GetGlobalGameInstance(const UWorld* WorldContextObject)
{
	UGlobalGameInstance* Inst = WorldContextObject->GetGameInstanceChecked<UGlobalGameInstance>();

	if (false == Inst->IsValidLowLevel())
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (false == Inst->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	return Inst;
}
