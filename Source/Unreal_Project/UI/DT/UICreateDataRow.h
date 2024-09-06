// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "UI/UIENum.h"
#include "Components/CanvasPanelSlot.h"
#include "UICreateDataRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FUICreateDataRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	FUICreateDataRow() {	}
	~FUICreateDataRow() {	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TSubclassOf<UUserWidget> Object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	bool StartOn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	EUIInputMode OpenMode = EUIInputMode::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	EUIInputMode CloseMode = EUIInputMode::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	FKey Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	FAnchorData InitScaleToPos;
};
