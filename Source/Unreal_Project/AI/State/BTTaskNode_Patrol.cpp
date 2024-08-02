// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/State/BTTaskNode_Patrol.h"
#include "Global/ProjectEnum.h"
#include "Unreal_Project.h"
#include "GlobalMainCharacter/GlobalCharacter.h"
#include "GlobalMainCharacter/DT/MainMonsterDataRow.h"
#include "Global/GloabalGameState.h"
#include "Global/GlobalBlueprintFunctionLibrary.h"
#include "Global/GlobalGameInstance.h"
#include "GlobalMainCharacter/GlobalCharacter.h"

EBTNodeResult::Type UBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::Patrol)
	{
		return EBTNodeResult::Type::Failed;
	}

	UGlobalGameInstance* Inst = UGlobalBlueprintFunctionLibrary::GetGlobalGameInstance(GetWorld());

	UMainMonsterData* MonsterData = GetValueAsObject<UMainMonsterData>(_OwnerComp, TEXT("MonsterData"));
	MonsterData->IdleTime = 0.0f;

	int Count = MonsterData->Data->PatrolCount;
	AGlobalCharacter* Character = GetActor<AGlobalCharacter>(_OwnerComp);
	FVector ActorPos = Character->GetActorLocation();
	ActorPos.Z = 0.0f;

	// Clear
	MonsterData->PatrolPoints.Empty();

	for (size_t i = 0; i < Count; i++)
	{
		// 길이는 1
		FVector RandomDir = Inst->GetRandomDir2D();
		RandomDir *= Inst->Random.FRandRange(MonsterData->Data->PatrolMinRange, MonsterData->Data->PatrolMaxRange);
		MonsterData->PatrolPoints.Add(ActorPos + RandomDir);
	}


	MonsterData->PatrolPoints.Add(ActorPos);

	// Character = nullptr;

	// 언리얼에서는 null체크를 할필요가 없고
	// 언리얼에서 유요한 체크를 
	if (false == Character->IsValidLowLevel())
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (ItemMeshs.Num() <= static_cast<uint8>(_Slot))"), __FUNCTION__, __LINE__);
		return EBTNodeResult::Aborted;
	}

	Character->ChangeAnimation(EMonsterAnimation::Walk);


	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	UMainMonsterData* MonsterData = GetValueAsObject<UMainMonsterData>(_OwnerComp, TEXT("MonsterData"));

	if (true == MonsterData->PatrolPoints.IsEmpty())
	{
		ChangeState(_OwnerComp, EMonsterState::Idle);
		return;
	}

	FVector TargetPoint = MonsterData->PatrolPoints[0];
	AGlobalCharacter* Character = GetActor<AGlobalCharacter>(_OwnerComp);
	FVector ActorPos = Character->GetActorLocation();
	ActorPos.Z = 0.0f;


	//// z를 제거해야할수도 있다.
	FVector Dir = TargetPoint - ActorPos;
	Character->AddMovementInput(Dir);

	if (Dir.Size() <= 10.0f)
	{
		MonsterData->PatrolPoints.RemoveAt(0);
		return;
	}

	AActor* TargetActor = CheckTarget(_OwnerComp, MonsterData->Data->SightRange, EObjectType::Player);

	if (nullptr == TargetActor)
	{
		return;
	}

	ChangeState(_OwnerComp, EMonsterState::PlayerToMove);
}
