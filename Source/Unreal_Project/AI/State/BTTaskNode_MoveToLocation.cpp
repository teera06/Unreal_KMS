// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/State/BTTaskNode_MoveToLocation.h"
#include "Global/ProjectEnum.h"
#include "Unreal_Project.h"
#include "GlobalMainCharacter/GlobalCharacter.h"
#include "GlobalMainCharacter/DT/MainMonsterDataRow.h"
#include "AI/AIController/MainAIController.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

EBTNodeResult::Type UBTTaskNode_MoveToLocation::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);
	// 이 노드의 업데이트 함수를 실행하라가 됩니다.
	// 그 업덷이트 함수가 종료되기 전까지는 지속적으로 우리눈에는 이 노드가 실행되고 있는 것으로 보입니다.
	// 이 노드들을 연결한 위쪽이 지금 Selector

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::MoveToLocation)
	{
		return EBTNodeResult::Type::Failed;
	}

	AGlobalCharacter* Character = GetActor<AGlobalCharacter>(_OwnerComp);
	Character->ChangeAnimation(EMonsterAnimation::Run);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_MoveToLocation::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	UMainMonsterData* MonsterData = GetValueAsObject<UMainMonsterData>(_OwnerComp, TEXT("MonsterData"));

	AGlobalCharacter* Character = GetActor<AGlobalCharacter>(_OwnerComp);
	AMainAIController* Con = GetController<AMainAIController>(_OwnerComp);
	FVector ActorPos = Character->GetActorLocation();
	ActorPos.Z = 0.0f;
	FVector Dir = MonsterData->TargetPos - ActorPos;
	Character->AddMovementInput(Dir);

	AActor* TargetActor = CheckTarget(_OwnerComp, MonsterData->Data->SightRange, EObjectType::Player);

	if (nullptr != TargetActor)
	{
		ChangeState(_OwnerComp, EMonsterState::PlayerToMove);
		return;
	}

	if (Dir.Size() <= 10.0f)
	{
		ChangeState(_OwnerComp, EMonsterState::Idle);
		return;
	}
}
