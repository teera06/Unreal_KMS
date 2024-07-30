// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GlobalBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECT_API UGlobalBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UGlobalBTTaskNode();
protected:
	template<typename EnumType>
	EnumType GetCurState(UBehaviorTreeComponent& _OwnerComp)
	{
		return static_cast<EnumType>(GetCurState(_OwnerComp));
	}

	uint8 GetCurState(UBehaviorTreeComponent& _OwnerComp);

	template<typename EnumType>
	void ChangeState(UBehaviorTreeComponent& _OwnerComp, EnumType _StateChange)
	{
		ChangeState(_OwnerComp, static_cast<uint8>(_StateChange));
	}

	void ChangeState(UBehaviorTreeComponent& _OwnerComp, uint8 _StateChange);

	template<typename OwnerType>
	OwnerType* GetActor(UBehaviorTreeComponent& _OwnerComp)
	{
		return Cast<OwnerType>(GetActor(_OwnerComp));
	}

	AActor* GetActor(UBehaviorTreeComponent& _OwnerComp);

	template<typename ConvertType>
	ConvertType* GetValueAsObject(UBehaviorTreeComponent& _OwnerComp, FName _Name)
	{
		return Cast<ConvertType>(GetValueAsObject(_OwnerComp, _Name));
	}

	// __
	FORCEINLINE UObject* GetValueAsObject(UBehaviorTreeComponent& _OwnerComp, FName _Name)
	{
		return _OwnerComp.GetBlackboardComponent()->GetValueAsObject(_Name);
	}

	FORCEINLINE void SetValueAsObject(UBehaviorTreeComponent& _OwnerComp, FName _Name, UObject* _Value)
	{
		_OwnerComp.GetBlackboardComponent()->SetValueAsObject(_Name, _Value);
	}
};