// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GlobalGameInstance.h"
#include "Unreal_Project.h"
#include "GlobalMainCharacter/DT/MainMonsterDataRow.h"
#include "UI/DA/UIGameSetting.h"
#include "ItemObject/GameItem.h"

void UGlobalGameInstance::Init()
{
	Super::Init();

	if (nullptr == PlayUIDataTable)
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (nullptr == MonsterDataTable)"), __FUNCTION__, __LINE__);
	}

	{
		TArray<FUICreateDataRow*> Data;

		TArray<FName> Names = PlayUIDataTable->GetRowNames();
		PlayUIDataTable->GetAllRows(TEXT(""), Data);

		for (size_t i = 0; i < Data.Num(); i++)
		{
			UIPlayWidgets.Add(Names[i].ToString(), *Data[i]);
		}
	}

	{
		for (size_t i = 0; i <UIGameSettingData->InvenCount; i++)
		{
			// 누구랑 메모리 생존을 함께 할거냐?
			UGameItem* Item = NewObject<UGameItem>(this);
			InventoryItems.Add(Item);
		}
	}
}

const FMainMonsterDataRow* UGlobalGameInstance::GetMonsterData(FName _Name)
{
	if (nullptr == MonsterTable)
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (nullptr == MonsterDataTable)"), __FUNCTION__, __LINE__);
	}

	FMainMonsterDataRow* MonsterData = MonsterTable->FindRow<FMainMonsterDataRow>(_Name, nullptr);

	if (nullptr == MonsterData)
	{
		UE_LOG(MyLog, Error, TEXT("%S(%u)> %s Name Data Is Nullptr"), __FUNCTION__, __LINE__, *_Name.ToString());
		return nullptr;
	}

	return MonsterData;
}
