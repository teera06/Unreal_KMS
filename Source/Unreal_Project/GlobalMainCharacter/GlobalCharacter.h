// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global/ProjectEnum.h"
#include "GlobalCharacter.generated.h"

UCLASS()
class UNREAL_PROJECT_API AGlobalCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGlobalCharacter();

	template<typename EnumType>
	void ChangeAnimation(EnumType _Type)
	{
		ChangeAnimation(static_cast<uint8>(_Type));
	}

	void ChangeAnimation(uint8 _Type);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(Category = "Contents",  VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	uint8 AniValue = 0;
};
