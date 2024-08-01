// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/State/BTTaskNode_PlayerToMove.h"
#include "Global/ProjectEnum.h"
#include "Unreal_Project.h"
#include "GlobalMainCharacter/GlobalCharacter.h"
#include "GlobalMainCharacter/DT/MainMonsterDataRow.h"
#include "AI/AIController/MainAIController.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Global/GlobalBlueprintFunctionLibrary.h"
#include "Global/GlobalGameInstance.h"

EBTNodeResult::Type UBTTaskNode_PlayerToMove::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
    Super::ExecuteTask(_OwnerComp, _NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::PlayerToMove)
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

	UMainMonsterData* MonsterData = GetValueAsObject<UMainMonsterData>(_OwnerComp, TEXT("MonsterData"));


	AActor* Target = GetValueAsObject<AActor>(_OwnerComp, TEXT("TargetActor"));

	if (false == Target->IsValidLowLevel())
	{
		ChangeState(_OwnerComp, EMonsterState::Idle);
		return;
	}

	AGlobalCharacter* Character = GetActor<AGlobalCharacter>(_OwnerComp);


	AActor* OldTarget = GetValueAsObject<AActor>(_OwnerComp, TEXT("TargetActor"));
	AActor* TargetActor = GetTarget(_OwnerComp, MonsterData->Data->SightRange, EObjectType::Player);

	if (nullptr == TargetActor)
	{
		MonsterData->TargetPosToOriginPos();
		ChangeState(_OwnerComp, EMonsterState::MoveToLocation);
		return;
	}

	// 무조건 가까운놈 쫓는다로 결정했다.
	// 참고로 기반이 다 되어있기 때문에 쉽게 짠다는걸 기억해라.
	if (OldTarget != TargetActor)
	{
		SetValueAsObject(_OwnerComp, TEXT("TargetActor"), TargetActor);
		return;
	}

	if (true == MonsterData->PathPoints.IsEmpty())
	{
		FVector Start = Character->GetActorLocation();
		FVector End = TargetActor->GetActorLocation();

		UNavigationPath* Path = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), Start, End, Character);
		MonsterData->PathPoints = Path->PathPoints;
		MonsterData->PathPoints.RemoveAt(0);
	}

//#if WITH_EDITOR
//		Path->EnableDebugDrawing(true);
//#endif
	//}

	AMainAIController* Con = GetController<AMainAIController>(_OwnerComp);

	FVector TargetLocation = Target->GetActorLocation();

	if (false == MonsterData->PathPoints.IsEmpty())
	{
		TargetLocation = MonsterData->PathPoints[0];

		FVector MonsterPos = Character->GetActorLocation();
		MonsterPos.Z = 0.0f;
		FVector CheckDir = (TargetLocation - MonsterPos);
		if (10.0f >= CheckDir.Size())
		{
			MonsterData->PathPoints.RemoveAt(0);
		}
	}

	FVector MoveDir = TargetLocation - Character->GetActorLocation();
	Character->AddMovementInput(MoveDir);

	FVector AttackRangeCheck = Target->GetActorLocation() - Character->GetActorLocation();
	if (AttackRangeCheck.Size() > MonsterData->Data->AttackRange)
	{
		return;
	}

	UGlobalGameInstance* Init = UGlobalBlueprintFunctionLibrary::GetGlobalGameInstance(GetWorld());
	Init->SetIsMonsterSkillAtt1(true);
	if (true == Init->GetIsMonsterSkillAtt1())
	{
		ChangeState(_OwnerComp, EMonsterState::SkillAttack1);
	}
	else
	{
		ChangeState(_OwnerComp, EMonsterState::Attack);
	}
	
}
