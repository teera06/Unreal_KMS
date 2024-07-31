// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GlobalBTTaskNode.h"
#include "Global/GloabalGameState.h"
#include "Global/GlobalBlueprintFunctionLibrary.h"
#include "Global/ProjectEnum.h"

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

AActor* UGlobalBTTaskNode::GetTarget(UBehaviorTreeComponent& _OwnerComp, float _Range, uint8 _TargetGroup, bool _ZIgnore /*= true*/)
{
	AGloabalGameState* GameState = UGlobalBlueprintFunctionLibrary::GetGloabalGameState(GetWorld());
	TArray<AActor*> Targets = GameState->GetGroup(EObjectType::Player);

	// ���ݹ����� �����;� �Ѵ�.
	AActor* TargetActor = nullptr;
	AActor* OwnerActor = GetActor(_OwnerComp);

	// ���� ����� Ÿ���� ã�ƾ� �Ѵ�.
	// float ��� �ִ밪
	float MinDis = TNumericLimits<float>::Max();
	for (size_t i = 0; i < Targets.Num(); i++)
	{
		FVector TargetPos = Targets[i]->GetActorLocation();
		FVector OwnerPos = OwnerActor->GetActorLocation();

		if (true == _ZIgnore)
		{
			TargetPos.Z = 0.0f;
			OwnerPos.Z = 0.0f;
		}

		FVector Dis = TargetPos - OwnerPos;
		float DisSize = Dis.Size();
		// ���ؼ� �����ٱ��� �ִ� �����
		if (DisSize >= _Range)
		{
			// ����
			continue;
		}

		// �� ����� ���Ͱ� �̹� �����Ѵ�.
		if (MinDis <= DisSize)
		{
			continue;
		}

		TargetActor = Targets[i];
		MinDis = DisSize;
	}

	return TargetActor;
}

AActor* UGlobalBTTaskNode::CheckTarget(UBehaviorTreeComponent& _OwnerComp, float _Range, uint8 Target, bool _ZIgnore /*= true*/)
{
	AActor* TargetActor = GetTarget(_OwnerComp, _Range, Target);

	if (nullptr == TargetActor)
	{
		_OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);
		return nullptr;
	}

	_OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), TargetActor);

	return TargetActor;
}