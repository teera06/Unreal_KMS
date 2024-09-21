// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GloabalGameState.generated.h"

UCLASS()
class UNREAL_PROJECT_API UActorGroup : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> Actors;
};
/**
 * 
 */
UCLASS()
class UNREAL_PROJECT_API AGloabalGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	
	// Game State �� Ŭ��� ������ �� ������ �ִ�. ����ȭ
	template<typename EnumType>
	void PushActor(EnumType _Index, AActor* _Actor)
	{
		PushActor(static_cast<uint8>(_Index), _Actor);
	}

	void PushActor(uint8 _Index, AActor* _Actor);

	template<typename EnumType>
	void PopActor(EnumType _Index, AActor* _Actor)
	{
		PopActor(static_cast<uint8>(_Index), _Actor);
	}

	void PopActor(uint8 _Index, AActor* _Actor);


	template<typename EnumType>
	TArray<AActor*> GetGroup(EnumType _Index)
	{
		return GetGroup(static_cast<uint8>(_Index));
	}

	TArray<AActor*> GetGroup(uint8 _Index);

private:
	// �׳� �ɹ������� ���ڱ� Empty
	// �������� null �̷���.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<int, UActorGroup*> AllActor;
	// �÷��̾� �׷�, ���� �׷� Actor ����

	
};
