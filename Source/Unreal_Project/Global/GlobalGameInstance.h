// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GlobalGameInstance.generated.h"

struct FMainMonsterDataRow;
class UUIGameSetting;
class UGameItem;
/**
 * 
 */
UCLASS()
class UNREAL_PROJECT_API UGlobalGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	FRandomStream Random;

	FVector GetRandomDir2D()
	{
		float DirX = Random.FRandRange(-100.0f, 100.0f);
		float DirY = Random.FRandRange(-100.0f, 100.0f);
		FVector Dir = FVector(DirX, DirY, 0.0f);
		return Dir.GetSafeNormal();
	}

	const struct FMainMonsterDataRow* GetMonsterData(FName _Name);





private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UDataTable* MonsterTable=nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UUIGameSetting* UIGameSettingData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UGameItem*> InventoryItems;
};
