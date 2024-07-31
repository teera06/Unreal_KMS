// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/OneHandSwordAnimNotifyState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MainActor/MainPlayer.h"

void UOneHandSwordAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AMainPlayer* PlayCharacter = MeshComp->GetOwner<AMainPlayer>();


	if (nullptr == PlayCharacter)
	{
		return;
	}

	float Damage = 0.0f;

	
	FHitResult Hit;

	UStaticMeshComponent* ItemMesh = PlayCharacter->GetStaticItemMesh()[static_cast<int>(EStaticItemSlot::RWeapon)];

	FTransform ItemTansForm = ItemMesh->GetSocketTransform(FName("AttackPoint"));
	//FVector ItemLocation = ItemMesh->GetSocketLocation(FName("AttackPoint"));

	//FTransform ItemTansForm=ItemMesh->GetRelativeTransform();
	FVector ItemRelativeLocationAdd = ItemMesh->GetRelativeLocation() + FVector(35.0f, 20.0f, 20.0f);

	FVector Start = ItemMesh->GetSocketLocation(FName("AttackPoint"));
	FVector End = UKismetMathLibrary::TransformLocation(ItemTansForm, ItemRelativeLocationAdd);
	//LineTraceSingle(CurWeapon, Start, End, ETraceTypeQuery::TraceTypeQuery1, false, Actors, EDrawDebugTrace::ForDuration, Hit, true, FLinearColor::Red, FLinearColor::Green, 5.0f);

	TArray<AActor*> AxeAtt;

	bool OKAtt = UKismetSystemLibrary::SphereTraceSingle(ItemMesh, Start, End, 50.0f, ETraceTypeQuery::TraceTypeQuery1, false, AxeAtt, EDrawDebugTrace::ForDuration, Hit, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
	//FVector Start;

	if (false == OKAtt)
	{
		return;
	}

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UGameplayStatics::ApplyDamage(ActorHit, 20.0f, nullptr, PlayCharacter, nullptr);
		//{
		//	AC_ZombieBase* Zombie = Cast<AC_ZombieBase>(ActorHit);

		//	if (Zombie)
		//	{
		//		//ZombieDieTrace(Zombie);
		//		PlayCharacter->WeaponSwingSound(Hit, true);
		//		Zombie->SetHP(25.0f);
		//		PlayCharacter->CreateZombieBlood(Hit);

		//		AC_MonsterAIBase* AIController = Cast<AC_MonsterAIBase>(Zombie->GetController());
		//		if (AIController != nullptr) {
		//			AIController->SetTargetActor(PlayCharacter);
		//		}

		//		PlayCharacter->MakeNoise(10.0f);



		//	}
		//}

	}
}

void UOneHandSwordAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UOneHandSwordAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
