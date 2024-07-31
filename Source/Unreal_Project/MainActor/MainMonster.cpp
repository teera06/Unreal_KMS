// Fill out your copyright notice in the Description page of Project Settings.


#include "MainActor/MainMonster.h"
#include "AI/AIController/MainAIController.h"
#include "Global/GlobalBlueprintFunctionLibrary.h"
#include "GlobalMainCharacter/DT/MainMonsterDataRow.h"
#include "Global/GlobalGameInstance.h"
#include "Global/ProjectEnum.h"
#include "Unreal_Project.h"
#include "BehaviorTree/BlackboardComponent.h"

void AMainMonster::BeginPlay()
{
	Super::BeginPlay();

	UGlobalGameInstance* Inst = UGlobalBlueprintFunctionLibrary::GetGlobalGameInstance(GetWorld());
	BaseData = Inst->GetMonsterData(FName("BaseMonster"));

	ObjectType = EObjectType::Monster;
	UGlobalBlueprintFunctionLibrary::PushActor(GetWorld(), ObjectType, this);

	{
		for (TPair<EMonsterAnimation, class UAnimMontage*> Montage : BaseData->AnimMontages)
		{
			GetGlobalAnimInstance()->PushAnimation(Montage.Key, Montage.Value);
		}
	}

	if (nullptr == GetController())
	{
		return;
	}

	if (nullptr == BaseData)
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (PortNumber == 0)"), __FUNCTION__, __LINE__);
		return;
	}

	// AI데이터 세팅
	{
		SettingData = NewObject<UMainMonsterData>(this);
		SettingData->Data = BaseData;

		SettingData->OriginPos = GetActorLocation();
		SettingData->OriginPos.Z = 0.0f;

		AMainAIController* Con = GetController<AMainAIController>();
		Con->GetBlackboardComponent()->SetValueAsObject(TEXT("MonsterData"), SettingData);
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
