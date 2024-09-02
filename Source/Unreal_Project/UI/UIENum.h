// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIENum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPlayUIType : uint8
{
	MiniMap,
	Status,
	Inventory,
};


UENUM(BlueprintType)
enum class EUIInputMode : uint8
{
	None,
	Game,
	UIOnly,
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None UMETA(DisplayName = "����"),
	Weapon UMETA(DisplayName = "����"),
	Armor UMETA(DisplayName = "��"),
	Potion UMETA(DisplayName = "����"),
};
