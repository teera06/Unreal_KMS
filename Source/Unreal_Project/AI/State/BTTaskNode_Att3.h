// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/GlobalBTTaskNode.h"
#include "BTTaskNode_Att3.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECT_API UBTTaskNode_Att3 : public UGlobalBTTaskNode
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAnimSequence* Anim;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MinusTime = 0.0f;
protected:
	// �� ��尡 ó�� ����ɶ� ���ɴϴ�.
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory);

	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds);
};
