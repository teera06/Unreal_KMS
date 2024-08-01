// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProjectEnum.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class EPlayerUpperAnimation : uint8
{
	Idle UMETA(DisplayName = "가만히있기"),
	Attack UMETA(DisplayName = "공격"),
};




UENUM(BlueprintType)
enum class EWeapon : uint8
{
	
	GreatSword UMETA(DisplayName = "대검"),
	OneHandSword UMETA(DisplayName = "한손검"),
	shield UMETA(DisplayName = "방패")
};


UENUM(BlueprintType)
enum class EItemType : uint8
{
	None UMETA(DisplayName = "에러"),
	Weapon UMETA(DisplayName = "무기"),
	Armor UMETA(DisplayName = "방어구"),
	Potion UMETA(DisplayName = "물약"),
};


UENUM(BlueprintType)
enum class ECharacterSlot : uint8
{
	LWeapon,
	RWeapon,
	SlotMax,
};

UENUM(BlueprintType)
enum class EObjectType : uint8
{
	Player,
	Monster,
	Max,
};

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Idle UMETA(DisplayName = "서있기"),
	Patrol UMETA(DisplayName = "서성이기"),
	PlayerToMove UMETA(DisplayName = "플레이어 쫓기"),
	MoveToLocation UMETA(DisplayName = "정해진 위치로 이동하기"),
	Attack UMETA(DisplayName = "공격"),
	Attack2 UMETA(DisplayName = "공격2"),
};

UENUM(BlueprintType)
enum class EMonsterAnimation : uint8
{
	Idle UMETA(DisplayName = "서있기"),
	Run UMETA(DisplayName = "달리기"),
	Attack UMETA(DisplayName = "평타0"),
	Attack2 UMETA(DisplayName = "평타1"),
	Attack3 UMETA(DisplayName = "평타2"),
};

UENUM(BlueprintType)
enum class EStaticItemSlot : uint8
{
	RWeapon UMETA(DisplayName = "무기"),
	LWeapon UMETA(DisplayName = "방패"),
	SlotMax
};
