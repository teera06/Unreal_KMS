// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GlobalAnimInstance.h"
#include "Unreal_Project.h"

void UGlobalAnimInstance::ChangeAnimation(uint8 Key)
{
	if (false == AnimMontages.Contains(Key))
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (false == AnimMontages.Contains(Key))"), __FUNCTION__, __LINE__);
		return;
	}

	UAnimMontage* Mon = AnimMontages[Key];

	// 이렇게 터트리지 않으면 
	if (nullptr == Mon)
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (nullptr == Mon)"), __FUNCTION__, __LINE__);
		return;
	}

	UAnimMontage* PrevMon = GetCurrentActiveMontage();

	// Mon 루프가 아닌게 중요해요.
	if (nullptr == PrevMon && nullptr != Mon)
	{
		// 
		// 애니메이션이 종료됐어요.
	}

	if (PrevMon != Mon)
	{
		Montage_Play(Mon);
	}
}

void UGlobalAnimInstance::PushAnimation(uint8 Key, UAnimMontage* _Montage)
{
	if (true == AnimMontages.Contains(Key))
	{
		return;
	}

	AnimMontages.Add(Key, _Montage);
}

uint8 UGlobalAnimInstance::GetAnimationKey(UAnimMontage* _AnimMontage)
{
	for (TPair<uint8, class UAnimMontage*> Pair : AnimMontages)
	{
		if (Pair.Value == _AnimMontage)
		{
			return Pair.Key;
		}
	}

	return -1;
}
