// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GlobalGameInstance.h"
#include "Unreal_Project.h"
#include "GlobalMainCharacter/DT/MainMonsterDataRow.h"

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
