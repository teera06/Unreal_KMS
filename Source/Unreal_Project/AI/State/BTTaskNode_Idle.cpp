// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/State/BTTaskNode_Idle.h"
#include "Global/ProjectEnum.h"
#include "Unreal_Project.h"
#include "GlobalMainCharacter/GlobalCharacter.h"
#include "GlobalMainCharacter/DT/MainMonsterDataRow.h"


EBTNodeResult::Type UBTTaskNode_Idle::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	// �⺻�� EBTNodeResult::Succeeded;
	Super::ExecuteTask(_OwnerComp, _NodeMemory);
	// �� ����� ������Ʈ �Լ��� �����϶� �˴ϴ�.
	// �� ���K��Ʈ �Լ��� ����Ǳ� �������� ���������� �츮������ �� ��尡 ����ǰ� �ִ� ������ ���Դϴ�.
	// �� ������ ������ ������ ���� Selector

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::Idle)
	{
		return EBTNodeResult::Type::Failed;
	}

	AGlobalCharacter* Character = GetActor<AGlobalCharacter>(_OwnerComp);

	// Character = nullptr;

	// �𸮾󿡼��� nullüũ�� ���ʿ䰡 ����
	// �𸮾󿡼� ������ üũ�� 
	if (false == Character->IsValidLowLevel())
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (ItemMeshs.Num() <= static_cast<uint8>(_Slot))"), __FUNCTION__, __LINE__);
		return EBTNodeResult::Aborted;
	}

	Character->ChangeAnimation(EMonsterAnimation::Idle);


	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Idle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	UMainMonsterData* MonsterData = GetValueAsObject<UMainMonsterData>(_OwnerComp, TEXT("MonsterData"));

	/*AGlobalGameState* GameState = UGlobalBlueprintFunctionLibrary::GetGlobalGameState(GetWorld());
	TArray<AActor*> Players = GameState->GetGroup(ETPSObjectType::Player);*/

	//if (true == Players.IsEmpty())
	//{
	//	// StateChange
	//	FinishLatentTask(_OwnerComp, EBTNodeResult::Aborted);
	//	return;
	//}

	/*AActor* TargetActor = CheckTarget(_OwnerComp, MonsterData->Data->SightRange, ETPSObjectType::Player);*/

	/*if (nullptr == TargetActor)
	{
		MonsterData->IdleTime += _DeltaSeconds;

		if (true == MonsterData->IsPatrol())
		{
			ChangeState(_OwnerComp, ETPSMonsterState::Patrol);
		}
		return;
	}

	ChangeState(_OwnerComp, ETPSMonsterState::MoveToPlayer);*/
	//return;
}
