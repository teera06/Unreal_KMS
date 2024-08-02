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
	// �⺻�� EBTNodeResult::Succeeded;
	Super::ExecuteTask(_OwnerComp, _NodeMemory);
	// �� ����� ������Ʈ �Լ��� �����϶� �˴ϴ�.
	// �� ���K��Ʈ �Լ��� ����Ǳ� �������� ���������� �츮������ �� ��尡 ����ǰ� �ִ� ������ ���Դϴ�.
	// �� ������ ������ ������ ���� Selector

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp); 
	// ���� ���� ���¸� �����忡�� ������, GetBlackboardComponent()->GetValueAsEnum(TEXT("StateValue"));

	// ���� ���°� Idle ���°� �ƴ϶��
	if (StateValue != EMonsterState::Idle)
	{
		return EBTNodeResult::Type::Failed; // ���������� �� ��尡 �����ߴ�.
	}

	AGlobalCharacter* Character = GetActor<AGlobalCharacter>(_OwnerComp); // ���� ���� ����

	// Character = nullptr;

	// �𸮾󿡼��� nullüũ�� ���ʿ䰡 ����
	// �𸮾󿡼� ������ üũ�� 
	if (false == Character->IsValidLowLevel()) // ���� ���Ͱ� ��ȿ���� �ʴ� ���
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (ItemMeshs.Num() <= static_cast<uint8>(_Slot))"), __FUNCTION__, __LINE__);
		return EBTNodeResult::Aborted; // �������� ������ �ƴ϶� ���α׷��� ���� ������ �ǹ��Ѵ�. 
	}

	Character->ChangeAnimation(EMonsterAnimation::Idle); // �ִϸ��̼� ����


	return EBTNodeResult::InProgress; // �� ��带 ���ӽ��Ѷ�. -> TickTask ����
}

void UBTTaskNode_Idle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	// ���� ������ ���̺��� ���� �����´�.
	UMainMonsterData* MonsterData = GetValueAsObject<UMainMonsterData>(_OwnerComp, TEXT("MonsterData"));
	
	// Game state ���� ������
	AGloabalGameState* GameState = UGlobalBlueprintFunctionLibrary::GetGloabalGameState(GetWorld());
	
	// Player �׷��� ������
	TArray<AActor*> Players = GameState->GetGroup(EObjectType::Player);

	// Player �׷��� ���� ���
	if (true == Players.IsEmpty())
	{
		//StateChange
		// �������� ������ �ƴ϶� ���α׷��� ���� ������ �ǹ��Ѵ�.
		// ��� ����
		FinishLatentTask(_OwnerComp, EBTNodeResult::Aborted);
		return;
	}

	// ���� �þ� ���� ���� Player�� ������
	AActor* TargetActor = CheckTarget(_OwnerComp, MonsterData->Data->SightRange, EObjectType::Player);

	// �÷��̾� ���� ���������� ��
	if (nullptr == TargetActor)
	{
		MonsterData->IdleTime += _DeltaSeconds;

		if (true == MonsterData->IsPatrol()) // Ž���� True �ΰ�� 
		{
			ChangeState(_OwnerComp, EMonsterState::Patrol); // ���� ü���� Ž��
		}
		return;
	}

	// �÷��̾ �ִ� ���
	ChangeState(_OwnerComp, EMonsterState::PlayerToMove); // �÷��̾� �߰� ����
	return;
}
