// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Global/ProjectEnum.h"
#include "GameItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)

class UNREAL_PROJECT_API UGameItem : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = "Item", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UUserWidget* SlotWidget;
	// EItemType = Weapon;
	UPROPERTY(Category = "Item", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Count = 0;

	/*UPROPERTY(Category = "Item", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FItemDataRow ItemData;*/

	int Index = -1;

	/*void Copy(UGameItem* _Data)
	{
		Count = _Data->Count;
		ItemData = _Data->ItemData;
	}*/
};
