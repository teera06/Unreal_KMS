// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UIGameSetting.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECT_API UUIGameSetting : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int InvenCount = 20;
};
