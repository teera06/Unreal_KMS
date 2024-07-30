// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GlobalBTTaskNode.h"

UGlobalBTTaskNode::UGlobalBTTaskNode()
{
	bNotifyTick = true;
}

AActor* UGlobalBTTaskNode::GetActor(UBehaviorTreeComponent& _OwnerComp)
{
	UObject* Object = _OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor"));
	return Cast<AActor>(Object);
}

void UGlobalBTTaskNode::ChangeState(UBehaviorTreeComponent& _OwnerComp, uint8 _StateChange)
{
	_OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("StateValue"), _StateChange);
	FinishLatentTask(_OwnerComp, EBTNodeResult::Failed);
}

uint8 UGlobalBTTaskNode::GetCurState(UBehaviorTreeComponent& _OwnerComp)
{
	return _OwnerComp.GetBlackboardComponent()->GetValueAsEnum(TEXT("StateValue"));
}



AController* UGlobalBTTaskNode::GetController(UBehaviorTreeComponent& _OwnerComp)
{
	return Cast<AController>(_OwnerComp.GetOwner());
}