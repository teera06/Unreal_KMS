// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalMainCharacter/GlobalCharacter.h"
#include "Unreal_Project.h"
#include "Global/GlobalGameInstance.h"
#include "Global/GlobalBlueprintFunctionLibrary.h"
// Sets default values

AGlobalCharacter::AGlobalCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetGenerateOverlapEvents(true);
	UEnum* Enum = StaticEnum<EStaticItemSlot>();

	for (size_t i = 0; i < static_cast<size_t>(EStaticItemSlot::SlotMax); i++)
	{
		FString Name = Enum->GetNameStringByValue(i);
		UStaticMeshComponent* NewSlotMesh = CreateDefaultSubobject<UStaticMeshComponent>(*Name);
		NewSlotMesh->SetupAttachment(GetMesh(), *Name);
		NewSlotMesh->SetCollisionProfileName(TEXT("NoCollision"));
		NewSlotMesh->SetGenerateOverlapEvents(true);
		NewSlotMesh->bHiddenInSceneCapture = true;
		StaticItemMeshs.Push(NewSlotMesh);
	}
}



UGlobalAnimInstance* AGlobalCharacter::GetGlobalAnimInstance()
{
	return AnimInst;
}

// Called when the game starts or when spawned
void AGlobalCharacter::BeginPlay()
{
	Super::BeginPlay();
	AnimInst = Cast<UGlobalAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AGlobalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if (nullptr != AnimInst)
	{
		AnimInst->ChangeAnimation(AniValue);
	}*/
}

// Called to bind functionality to input
void AGlobalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGlobalCharacter::EndPlay(EEndPlayReason::Type Reason)
{
	Super::EndPlay(Reason);
	UGlobalBlueprintFunctionLibrary::PopActor(GetWorld(), ObjectType, this);
}

void AGlobalCharacter::ChangeSlotMesh(EStaticItemSlot _Slot, UStaticMesh* _Mesh)
{
	uint8 SlotIndex = static_cast<uint8>(_Slot);
	if (StaticItemMeshs.Num() <= SlotIndex)
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (ItemMeshs.Num() <= static_cast<uint8>(_Slot))"), __FUNCTION__, __LINE__);
		return;
	}

	UGlobalGameInstance* Inst = UGlobalBlueprintFunctionLibrary::GetGlobalGameInstance(GetWorld());

	//UStaticMesh* FindMesh = Inst->GetStaticMesh(_MeshName);

	StaticItemMeshs[SlotIndex]->SetStaticMesh(_Mesh);
}