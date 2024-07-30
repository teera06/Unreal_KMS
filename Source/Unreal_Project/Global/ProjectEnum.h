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
	Idle UMETA(DisplayName = "�������ֱ�"),
	Attack UMETA(DisplayName = "����"),
};




UENUM(BlueprintType)
enum class EWeapon : uint8
{
	
	GreatSword UMETA(DisplayName = "���"),
	OneHandSword UMETA(DisplayName = "�Ѽհ�"),
	shield UMETA(DisplayName = "����")
};


UENUM(BlueprintType)
enum class EItemType : uint8
{
	None UMETA(DisplayName = "����"),
	Weapon UMETA(DisplayName = "����"),
	Armor UMETA(DisplayName = "��"),
	Potion UMETA(DisplayName = "����"),
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
	Idle UMETA(DisplayName = "���ֱ�"),
	Patrol UMETA(DisplayName = "�����̱�"),
	MoveToPlayer UMETA(DisplayName = "�÷��̾� �ѱ�"),
	MoveToLocation UMETA(DisplayName = "������ ��ġ�� �̵��ϱ�"),
	Attack UMETA(DisplayName = "����"),
};

UENUM(BlueprintType)
enum class EMonsterAnimation : uint8
{
	Idle UMETA(DisplayName = "���ֱ�"),
	Run UMETA(DisplayName = "�޸���"),
	Attack0 UMETA(DisplayName = "��Ÿ0"),
	Attack1 UMETA(DisplayName = "��Ÿ1"),
	Attack2 UMETA(DisplayName = "��Ÿ2"),
};
