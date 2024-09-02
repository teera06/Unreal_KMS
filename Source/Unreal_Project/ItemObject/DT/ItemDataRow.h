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
	int Value=0; // ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	EItemType Type= EItemType::None; // ������ Ÿ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int MaxCount = 99; // �ִ� ����

	// ���Ͱ� �׾ ��������� �� �Ž�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	UStaticMesh* DropMesh=nullptr; // ��� �޽�

	// �κ��丮�� �������� ���� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	UTexture2D* Tex=nullptr;
};
