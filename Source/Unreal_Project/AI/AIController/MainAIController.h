// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MainAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECT_API AMainAIController : public AAIController
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void ChangeAIState(uint8 _StateType);

};
