// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIController/MainAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void AMainAIController::ChangeAIState(uint8 _StateType)
{
	// ������ ������Ʈ
	UBlackboardComponent* BB = GetBlackboardComponent();
	BB->SetValueAsEnum(TEXT("StateValue"), _StateType);
}
