// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalMainCharacter/GlobalCharacter.h"
#include "Global/GlobalAnimInstance.h"
// Sets default values

AGlobalCharacter::AGlobalCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGlobalCharacter::ChangeAnimation(uint8 _Type)
{
	AniValue = _Type;
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

}

// Called to bind functionality to input
void AGlobalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

