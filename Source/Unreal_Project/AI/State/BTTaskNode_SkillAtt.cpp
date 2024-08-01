// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/State/BTTaskNode_SkillAtt.h"
#include "Global/ProjectEnum.h"
#include "Unreal_Project.h"
#include "GlobalMainCharacter/GlobalCharacter.h"
#include "GlobalMainCharacter/DT/MainMonsterDataRow.h"
#include "Global/GloabalGameState.h"
#include "Global/GlobalBlueprintFunctionLibrary.h"
#include "Global/GlobalGameInstance.h"
#include "GlobalMainCharacter/GlobalCharacter.h"

EBTNodeResult::Type UBTTaskNode_SkillAtt::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}

void UBTTaskNode_SkillAtt::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{

}
