// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GlobalGameInstance.generated.h"

struct FMainMonsterDataRow;
/**
 * 
 */
UCLASS()
class UNREAL_PROJECT_API UGlobalGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	const struct FMainMonsterDataRow* GetMonsterData(FName _Name);
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UDataTable* MonsterTable=nullptr;
};
