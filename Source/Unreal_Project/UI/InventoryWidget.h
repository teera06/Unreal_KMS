// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/DragWidget.h"
#include "DragWidget.h"
#include "Components/TileView.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECT_API UInventoryWidget : public UDragWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void TileViewInitialze(UTileView* _TileView, int _InitCount, TArray<UGameItem*> _ItemDatas);

	UFUNCTION(BlueprintCallable)
	bool PushGameItemToEmpty(class UGameItem* _Item);

	UFUNCTION(BlueprintCallable)
	bool PushItemToIndex(UGameItem* _Item, int _SlotIndex);

	//// 빈 아이템 슬롯을 찾아서 자동으로 넣어주는 것.
	UFUNCTION(BlueprintCallable)
	bool PushItemToEmpty(UGameItem* _Item);

	/*UFUNCTION(BlueprintCallable)
	void PushItemToIndexToData(FItemDataRow _Item, int _SlotIndex);*/

	//// 빈 아이템 슬롯을 찾아서 자동으로 넣어주는 것.
	//UFUNCTION(BlueprintCallable)
	//void PushItemToEmptyToData(FItemDataRow _Item);


	UFUNCTION(BlueprintCallable)
	int GetEmptySlotIndex();

	UPROPERTY()
	TArray<UGameItem*> ItemDatasCopy;

	//// Test용 함수
	//UFUNCTION(BlueprintPure)
	//UGameItem* MakeItemDataToTest(int Count, UDataTable* _DataTable, FName _Key);

	UFUNCTION(BlueprintPure)
	UGameItem* MakeItemDataToData(int Count, FItemDataRow _Item);

	UFUNCTION(BlueprintCallable)
	void SlotAdd(UWidget* _Widget, UObject* _Data);
};
