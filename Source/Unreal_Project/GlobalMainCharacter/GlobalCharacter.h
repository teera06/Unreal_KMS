// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global/ProjectEnum.h"
#include "Global/GlobalAnimInstance.h"
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
		if (AnimInst == nullptr)
		{
			return;
		}

		AnimInst->ChangeAnimation(static_cast<uint8>(_Type));
	}

	FORCEINLINE TArray<UStaticMeshComponent*> GetStaticItemMesh() const
	{
		return StaticItemMeshs;
	}

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void ChangeSlotMesh(EStaticItemSlot _Slot, UStaticMesh* _Mesh);


	UGlobalAnimInstance* GetGlobalAnimInstance();

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*> StaticItemMeshs;

private:


	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UGlobalAnimInstance* AnimInst = nullptr;

	UPROPERTY(Category = "Contents",  VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	uint8 AniValue = 0;
};
