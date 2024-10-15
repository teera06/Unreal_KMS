// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryWidget.h"
#include "UI/InvenSlot.h"
#include "ItemObject/GameItem.h"
void UInventoryWidget::TileViewInitialze(UTileView* _TileView, int _InitCount, TArray<UGameItem*> _ItemDatas)
{
	_TileView->ClearListItems();
	// ItemDataArray.Empty();

	if (_ItemDatas.Num() != _InitCount)
	{
		return;
	}


	for (size_t i = 0; i < _InitCount; i++)
	{
		_ItemDatas[i]->Index = i;
		ItemDatasCopy.Add(_ItemDatas[i]);
		_TileView->AddItem(_ItemDatas[i]);
	}
}

bool UInventoryWidget::PushGameItemToEmpty(UGameItem* _Item)
{
	/*const FItemDataRow* ItemData = _Item->GetItemTable();

	UGameItem* NewItem = MakeItemDataToData(_Item->GetCount(), *ItemData);*/

	return false;
}

bool UInventoryWidget::PushItemToIndex(UGameItem* _Item, int _SlotIndex)
{
	if (0 > _SlotIndex)
	{
		return false;
	}

	if (_SlotIndex >= ItemDatasCopy.Num())
	{
		return false;
	}

	ItemDatasCopy[_SlotIndex]->Copy(_Item);
	return true;
}

bool UInventoryWidget::PushItemToEmpty(UGameItem* _Item)
{
	return PushItemToIndex(_Item, GetEmptySlotIndex());
}

int UInventoryWidget::GetEmptySlotIndex()
{
	// 이런거 하면 큰일난다.
	for (size_t i = 0; i < ItemDatasCopy.Num(); i++)
	{
		if (ItemDatasCopy[i]->Count == 0)
		{
			return i;
		}
	}

	return -1;
}

UGameItem* UInventoryWidget::MakeItemDataToData(int Count, FItemDataRow _Item)
{
	UGameItem* ItemData = NewObject<UGameItem>(this);
	ItemData->Count = Count;
	ItemData->ItemData = _Item;

	return ItemData;
}

void UInventoryWidget::SlotAdd(UWidget* _Widget, UObject* _Data)
{
	UInvenSlot* SlotWidget = Cast<UInvenSlot>(_Widget);

	UGameItem* ItemData = Cast<UGameItem>(_Data);
	ItemData->SlotWidget = SlotWidget;
	SlotWidget->Init(ItemData);

	SlotWidget->Index = ItemData->Index;

	SlotWidget->SetItemCount(ItemData->Count);
}


