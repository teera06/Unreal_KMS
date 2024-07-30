// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalMainCharacter/GlobalCharacter.h"
#include "MainMonster.generated.h"

class AMainAIController;
class UMainMonsterData;
struct FMainMonsterDataRow;

/**
 * 
 */
UCLASS()
class UNREAL_PROJECT_API AMainMonster : public AGlobalCharacter
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	AMainAIController* GetMainAIController();

private:
	UPROPERTY()
	UMainMonsterData* SettingData=nullptr;

	const FMainMonsterDataRow* BaseData=nullptr;
};
