// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalMainCharacter/DT/MainMonsterDataRow.h"

bool UMainMonsterData::IsPatrol()
{
	return Data->PatrolTime <= IdleTime;
}
