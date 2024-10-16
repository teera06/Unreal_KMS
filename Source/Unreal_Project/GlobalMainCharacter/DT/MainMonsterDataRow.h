// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Global/ProjectEnum.h"
#include "MainMonsterDataRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UNREAL_PROJECT_API FMainMonsterDataRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SightRange = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRange = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Att = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double HP = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double PatrolTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PatrolCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PatrolMinRange = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PatrolMaxRange = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EMonsterAnimation, class UAnimMontage* > AnimMontages;
};

UCLASS()
class UMainMonsterData : public UObject
{
	GENERATED_BODY()

public:
	const FMainMonsterDataRow* Data;

	UPROPERTY()
	TArray<FVector> PatrolPoints;
	UPROPERTY()
	TArray<FVector> PathPoints;
	UPROPERTY()
	float IdleTime = 0.0f;
	UPROPERTY()
	float AttackTime = 0.0f;
	UPROPERTY()
	int ComboAtt = 0;
	UPROPERTY()
	FVector OriginPos = FVector::ZeroVector;
	UPROPERTY()
	FVector TargetPos;
	UPROPERTY()
	bool IsGround = false;

	UFUNCTION()
	bool IsPatrol();

	FORCEINLINE void TargetPosToOriginPos()
	{
		TargetPos = OriginPos;
	}
};