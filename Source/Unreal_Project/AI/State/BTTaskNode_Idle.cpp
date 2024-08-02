// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/State/BTTaskNode_Idle.h"
#include "Global/ProjectEnum.h"
#include "Unreal_Project.h"
#include "GlobalMainCharacter/GlobalCharacter.h"
#include "GlobalMainCharacter/DT/MainMonsterDataRow.h"
#include "Global/GloabalGameState.h"
#include "Global/GlobalBlueprintFunctionLibrary.h"

EBTNodeResult::Type UBTTaskNode_Idle::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	// 기본이 EBTNodeResult::Succeeded;
	Super::ExecuteTask(_OwnerComp, _NodeMemory);
	// 이 노드의 업데이트 함수를 실행하라가 됩니다.
	// 그 업덷이트 함수가 종료되기 전까지는 지속적으로 우리눈에는 이 노드가 실행되고 있는 것으로 보입니다.
	// 이 노드들을 연결한 위쪽이 지금 Selector

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp); 
	// 현재 몬스터 상태를 블랙보드에서 가져옴, GetBlackboardComponent()->GetValueAsEnum(TEXT("StateValue"));

	// 현재 상태가 Idle 상태가 아니라면
	if (StateValue != EMonsterState::Idle)
	{
		return EBTNodeResult::Type::Failed; // 로직적으로 이 노드가 실패했다.
	}

	AGlobalCharacter* Character = GetActor<AGlobalCharacter>(_OwnerComp); // 몬스터 액터 정보

	// Character = nullptr;

	// 언리얼에서는 null체크를 할필요가 없고
	// 언리얼에서 유요한 체크를 
	if (false == Character->IsValidLowLevel()) // 몬스터 액터가 유효하지 않는 경우
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (ItemMeshs.Num() <= static_cast<uint8>(_Slot))"), __FUNCTION__, __LINE__);
		return EBTNodeResult::Aborted; // 로직적인 오류가 아니라 프로그래밍 적인 오류를 의미한다. 
	}

	Character->ChangeAnimation(EMonsterAnimation::Idle); // 애니메이션 변경


	return EBTNodeResult::InProgress; // 이 노드를 지속시켜라. -> TickTask 실행
}

void UBTTaskNode_Idle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	// 몬스터 데이터 테이블의 값을 가져온다.
	UMainMonsterData* MonsterData = GetValueAsObject<UMainMonsterData>(_OwnerComp, TEXT("MonsterData"));
	
	// Game state 값을 가져옴
	AGloabalGameState* GameState = UGlobalBlueprintFunctionLibrary::GetGloabalGameState(GetWorld());
	
	// Player 그룹을 가져옴
	TArray<AActor*> Players = GameState->GetGroup(EObjectType::Player);

	// Player 그룹이 없는 경우
	if (true == Players.IsEmpty())
	{
		//StateChange
		// 로직적인 오류가 아니라 프로그래밍 적인 오류를 의미한다.
		// 노드 종료
		FinishLatentTask(_OwnerComp, EBTNodeResult::Aborted);
		return;
	}

	// 몬스터 시야 범위 안의 Player를 가져옴
	AActor* TargetActor = CheckTarget(_OwnerComp, MonsterData->Data->SightRange, EObjectType::Player);

	// 플레이어 값을 못가져왔을 때
	if (nullptr == TargetActor)
	{
		MonsterData->IdleTime += _DeltaSeconds;

		if (true == MonsterData->IsPatrol()) // 탐색이 True 인경우 
		{
			ChangeState(_OwnerComp, EMonsterState::Patrol); // 상태 체인지 탐색
		}
		return;
	}

	// 플레이어가 있는 경우
	ChangeState(_OwnerComp, EMonsterState::PlayerToMove); // 플레이어 추격 상태
	return;
}
