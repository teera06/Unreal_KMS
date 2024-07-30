// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GlobalBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

#if WITH_EDITOR
void UGlobalBlueprintFunctionLibrary::DebugTextPrint(UWorld* _World, FString Text)
{

	APlayerController* Con = UGameplayStatics::GetPlayerController(_World, 0);
	// UI가 입력과 관련이 많기 때문에 HUD를 찾아내려면 
	//AGlobalHUD* Global = Cast<AGlobalHUD>(Con->GetHUD());

	/*if (nullptr == Global)
	{
		return;
	}*/

	/*Global->AddDebugString(Text);*/
}

#endif
