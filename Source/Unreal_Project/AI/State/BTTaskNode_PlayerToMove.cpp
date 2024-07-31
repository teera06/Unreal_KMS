// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/State/BTTaskNode_PlayerToMove.h"
#include "Global/ProjectEnum.h"
#include "Unreal_Project.h"
#include "GlobalMainCharacter/GlobalCharacter.h"
#include "GlobalMainCharacter/DT/MainMonsterDataRow.h"

EBTNodeResult::Type UBTTaskNode_PlayerToMove::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
    Super::ExecuteTask(_OwnerComp, _NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::MoveToPlayer)
	{
		return EBTNodeResult::Type::Failed;
	}


	AGlobalCharacter* Character = GetActor<AGlobalCharacter>(_OwnerComp);

	// Character = nullptr;

	// 언리얼에서는 null체크를 할필요가 없고
	// 언리얼에서 유요한 체크를 
	if (false == Character->IsValidLowLevel())
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (ItemMeshs.Num() <= static_cast<uint8>(_Slot))"), __FUNCTION__, __LINE__);
		return EBTNodeResult::Aborted;
	}
	Character->ChangeAnimation(EMonsterAnimation::Run);


	// 이 노드의 업데이트 함수를 실행하라가 됩니다.
	// 그 업덷이트 함수가 종료되기 전까지는 지속적으로 우리눈에는 이 노드가 실행되고 있는 것으로 보입니다.
	// 이 노드들을 연결한 위쪽이 지금 Selector
	return EBTNodeResult::InProgress;
}

void UBTTaskNode_PlayerToMove::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
    Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
}
