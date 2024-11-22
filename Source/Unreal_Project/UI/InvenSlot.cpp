// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InvenSlot.h"
#include "UI/InventoryWidget.h"

void UInvenSlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInvenSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}

void UInvenSlot::SetItemCount(int Count)
{
}

void UInvenSlot::SetItemData(UGameItem* _SlotData)
{
}

void UInvenSlot::Init(UGameItem* _Data)
{
	if (nullptr != IconWidget)
	{
		return;
	}

	Data = _Data;

	IconWidget = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
	ItemCountWidget = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));
}

bool UInvenSlot::IsDrag()
{
	return false;
}

void UInvenSlot::DropTest()
{
}

void UInvenSlot::Drop(UInvenSlot* _OtherSlot)
{
	if (_OtherSlot == this)
	{
		return;
	}

	int a = 0;

}

