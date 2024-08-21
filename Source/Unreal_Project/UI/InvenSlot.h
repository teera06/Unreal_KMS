// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InvenSlot.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECT_API UInvenSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetItemCount(int Count);


	UFUNCTION(BlueprintCallable)
	void SetItemData(class UGameItem* _SlotData);

	UFUNCTION(BlueprintCallable)
	void Init(UGameItem* _Data);

	UFUNCTION(BlueprintPure)
	bool IsDrag();


	UFUNCTION(BlueprintCallable)
	void DropTest();

	UFUNCTION(BlueprintCallable)
	void Drop(UInvenSlot* _OtherSlot);


	int Index = -1;

private:
	UPROPERTY()
	UImage* IconWidget = nullptr;

	UPROPERTY()
	UTextBlock* ItemCountWidget = nullptr;

	UGameItem* Data = nullptr;
	

};
