// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/State/BTTaskNode_AttDelay.h"
#include "Global/ProjectEnum.h"
#include "Unreal_Project.h"
#include "GlobalMainCharacter/GlobalCharacter.h"
#include "GlobalMainCharacter/DT/MainMonsterDataRow.h"
#include "AI/AIController/MainAIController.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Global/GlobalBlueprintFunctionLibrary.h"
#include "Global/GlobalGameInstance.h"

EBTNodeResult::Type UBTTaskNode_AttDelay::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, _NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	/*if (StateValue != EMonsterState::AttDelay)
	{
		return EBTNodeResult::Type::Failed;
	}*/

	AGlobalCharacter* Character = GetActor<AGlobalCharacter>(_OwnerComp);

	// Character = nullptr;

	// �𸮾󿡼��� nullüũ�� ���ʿ䰡 ����
	// �𸮾󿡼� ������ üũ�� 
	if (false == Character->IsValidLowLevel())
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (ItemMeshs.Num() <= static_cast<uint8>(_Slot))"), __FUNCTION__, __LINE__);
		return EBTNodeResult::Aborted;
	}
	Character->ChangeAnimation(EMonsterAnimation::AttDelay);


	// �� ����� ������Ʈ �Լ��� �����϶� �˴ϴ�.
	// �� ���K��Ʈ �Լ��� ����Ǳ� �������� ���������� �츮������ �� ��尡 ����ǰ� �ִ� ������ ���Դϴ�.
	// �� ������ ������ ������ ���� Selector
	return EBTNodeResult::InProgress;
}

void UBTTaskNode_AttDelay::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	UMainMonsterData* MonsterData = GetValueAsObject<UMainMonsterData>(_OwnerComp, TEXT("MonsterData"));


	AActor* Target = GetValueAsObject<AActor>(_OwnerComp, TEXT("TargetActor"));

	// �߰� ����� ã�����Ѱ��
	if (false == Target->IsValidLowLevel())
	{
		ChangeState(_OwnerComp, EMonsterState::Idle);
		return;
	}

	AGlobalCharacter* Character = GetActor<AGlobalCharacter>(_OwnerComp);


	AActor* OldTarget = GetValueAsObject<AActor>(_OwnerComp, TEXT("TargetActor"));
	AActor* TargetActor = GetTarget(_OwnerComp, MonsterData->Data->SightRange, EObjectType::Player);

	// �߰� ����� �þ翡�� ��� ���
	if (nullptr == TargetActor)
	{
		MonsterData->TargetPosToOriginPos();
		ChangeState(_OwnerComp, EMonsterState::MoveToLocation);
		return;
	}

	// ������ ������ �Ѵ´ٷ� �����ߴ�.
	// ����� ����� �� �Ǿ��ֱ� ������ ���� §�ٴ°� ����ض�.
	if (OldTarget != TargetActor)
	{
		SetValueAsObject(_OwnerComp, TEXT("TargetActor"), TargetActor);
		return;
	}

	AMainAIController* Con = GetController<AMainAIController>(_OwnerComp);

	if (MonsterData->ComboAtt % 2 == 0)
	{
		Character->AddMovementInput(FVector(-100.0f, 0.0f, 0.0f));
	}
	else
	{
		Character->AddMovementInput(FVector(100.0f, 0.0f, 0.0f));
	}


	FVector AttackRangeCheck = Target->GetActorLocation() - Character->GetActorLocation();
	if (AttackRangeCheck.Size() > MonsterData->Data->AttackRange)
	{
		return;
	}

	MinusTime -= _DeltaSeconds;

	if (MinusTime <= 0.0f)
	{
		ChangeState(_OwnerComp, EMonsterState::PlayerToMove);
		return;
	}
}
