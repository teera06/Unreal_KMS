// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalMainCharacter/GlobalCharacter.h"
#include "MainPlayer.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECT_API AMainPlayer : public AGlobalCharacter
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	// Called to bind functionality to input
private:
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsAttCpp = false;
};
