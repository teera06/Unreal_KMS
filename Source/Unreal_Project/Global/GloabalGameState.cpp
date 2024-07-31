// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GloabalGameState.h"

void AGloabalGameState::PushActor(uint8 _Index, AActor* _Actor)
{
	if (false == AllActor.Contains(_Index))
	{
		// ��κ� �����͸� �����մϴ�.
		// unreal ��������
		// AllActor.SetNum(_Index);

		// new UActorGroup

		AllActor.Add(_Index, NewObject<UActorGroup>());
	}

	AllActor[_Index]->Actors.Add(_Actor);
}

void AGloabalGameState::PopActor(uint8 _Index, AActor* _Actor)
{
	if (false == AllActor.Contains(_Index))
	{
		AllActor.Add(_Index, NewObject<UActorGroup>());
	}

	AllActor[_Index]->Actors.Remove(_Actor);
}

TArray<AActor*> AGloabalGameState::GetGroup(uint8 _Index)
{
	if (false == AllActor.Contains(_Index))
	{
		AllActor.Add(_Index, NewObject<UActorGroup>());
	}

	return AllActor[_Index]->Actors;
}
