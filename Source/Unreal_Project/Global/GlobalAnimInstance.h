// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GlobalAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECT_API UGlobalAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	template<typename EnumType>
	void ChangeAnimation(EnumType Key)
	{
		ChangeAnimation(static_cast<uint8>(Key));
	}

	void ChangeAnimation(uint8 Key);

	template<typename EnumType>
	void PushAnimation(EnumType Key, class UAnimMontage* _Montage)
	{
		PushAnimation(static_cast<uint8>(Key), _Montage);
	}

	void PushAnimation(uint8 Key, class UAnimMontage* _Montage);

	TMap<int, class UAnimMontage* > GetAnimMontages()
	{
		return AnimMontages;
	}

	uint8 GetAnimationKey(class UAnimMontage* _AnimMontage);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<int32, class UAnimMontage* > AnimMontages;
};
