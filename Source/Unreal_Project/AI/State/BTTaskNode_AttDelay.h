// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/GlobalBTTaskNode.h"
#include "BTTaskNode_AttDelay.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECT_API UBTTaskNode_AttDelay : public UGlobalBTTaskNode
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MinusTime = 3.0f;
protected:
	// 이 노드가 처음 실행될때 들어옵니다.
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory);

	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds);
};
