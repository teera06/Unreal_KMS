// Fill out your copyright notice in the Description page of Project Settings.


#include "MainActor/MainMonster.h"
#include "AI/AIController/MainAIController.h"
#include "Global/GlobalBlueprintFunctionLibrary.h"
#include "GlobalMainCharacter/DT/MainMonsterDataRow.h"
#include "Global/GlobalGameInstance.h"
#include "Global/ProjectEnum.h"

void AMainMonster::BeginPlay()
{
	Super::BeginPlay();

	UGlobalGameInstance* Inst = UGlobalBlueprintFunctionLibrary::GetGlobalGameInstance(GetWorld());
	BaseData = Inst->GetMonsterData("BaseMonster");

	{
		for (TPair<EMonsterAnimation, class UAnimMontage*> Montage : BaseData->AnimMontages)
		{
			//GetGlobalAnimInstance()->PushAnimation(Montage.Key, Montage.Value);
		}
	}
}

void AMainMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AMainAIController* AMainMonster::GetMainAIController()
{
	AController* Con = GetController();

	return Cast<AMainAIController>(GetController());
}
