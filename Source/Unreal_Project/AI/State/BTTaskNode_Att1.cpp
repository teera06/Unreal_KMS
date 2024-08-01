// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/State/BTTaskNode_Att1.h"
#include "Global/ProjectEnum.h"
#include "Unreal_Project.h"
#include "GlobalMainCharacter/GlobalCharacter.h"
#include "GlobalMainCharacter/DT/MainMonsterDataRow.h"
#include "Global/GloabalGameState.h"
#include "Global/GlobalBlueprintFunctionLibrary.h"
#include "Global/GlobalGameInstance.h"
#include "GlobalMainCharacter/GlobalCharacter.h"

EBTNodeResult::Type UBTTaskNode_Att1::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState State = GetCurState<EMonsterState>(_OwnerComp);

	if (State != EMonsterState::Attack)
	{
		return EBTNodeResult::Type::Failed;
	}

	AGlobalCharacter* Character = GetActor<AGlobalCharacter>(_OwnerComp);
	if (false == Character->IsValidLowLevel())
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (ItemMeshs.Num() <= static_cast<uint8>(_Slot))"), __FUNCTION__, __LINE__);
		return EBTNodeResult::Aborted;
	}

	// 회전하고 애니메이션 체인지
	RotationToTargetActor(_OwnerComp);

	Character->ChangeAnimation(EMonsterAnimation::Attack);

	AActor* Target = GetValueAsObject<AActor>(_OwnerComp, TEXT("TargetActor"));

	UMainMonsterData* MonsterData = GetValueAsObject<UMainMonsterData>(_OwnerComp, TEXT("MonsterData"));

	if (nullptr != Anim)
	{
		MonsterData->AttackTime = Anim->GetPlayLength();
	}

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_Att1::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	UMainMonsterData* MonsterData = GetValueAsObject<UMainMonsterData>(_OwnerComp, TEXT("MonsterData"));
	AGlobalCharacter* Character = GetActor<AGlobalCharacter>(_OwnerComp);
	MonsterData->AttackTime -= _DeltaSeconds;
	
	if (0.0f < (MonsterData->AttackTime - MinusTime))
	{
		return;
	}

	AActor* TargetActor = CheckTarget(_OwnerComp, MonsterData->Data->SightRange, EObjectType::Player);




	if (nullptr != TargetActor)
	{
		FVector Dir = TargetActor->GetActorLocation() - Character->GetActorLocation();
		if (Dir.Size() < MonsterData->Data->AttackRange)
		{
			ChangeState(_OwnerComp, EMonsterState::Attack2);
			return;
		}
	}


	ChangeState(_OwnerComp, EMonsterState::Idle);
}
