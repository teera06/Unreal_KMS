// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Global/ProjectEnum.h"
#include "GameItem.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)

struct UNREAL_PROJECT_API FGameItem : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int Value=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	EItemType Type =EItemType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int MaxCount = 99;

	// 몬스터가 죽어서 드랍됐을대 뜰 매쉬
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	UStaticMesh* DropMesh=nullptr;

	// 인벤토리에 들어왔을때 보일 아이콘
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	UTexture2D* Tex=nullptr;
};
