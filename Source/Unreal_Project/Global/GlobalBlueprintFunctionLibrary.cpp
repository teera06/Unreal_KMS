// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GlobalBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

#if WITH_EDITOR
void UGlobalBlueprintFunctionLibrary::DebugTextPrint(UWorld* _World, FString Text)
{

	APlayerController* Con = UGameplayStatics::GetPlayerController(_World, 0);
	// UI�� �Է°� ������ ���� ������ HUD�� ã�Ƴ����� 
	//AGlobalHUD* Global = Cast<AGlobalHUD>(Con->GetHUD());

	/*if (nullptr == Global)
	{
		return;
	}*/

	/*Global->AddDebugString(Text);*/
}

#endif
