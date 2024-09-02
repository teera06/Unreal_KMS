// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UI/UIENum.h"
#include "ItemDataRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemDataRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	FItemDataRow() {}
	~FItemDataRow() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int Value=0; // 개수

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	EItemType Type= EItemType::None; // 아이템 타입

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int MaxCount = 99; // 최대 개수

	// 몬스터가 죽어서 드랍됐을대 뜰 매쉬
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	UStaticMesh* DropMesh=nullptr; // 드랍 메시

	// 인벤토리에 들어왔을때 보일 아이콘
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	UTexture2D* Tex=nullptr;
};
