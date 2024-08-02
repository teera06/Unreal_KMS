// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DragWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Global/GlobalBlueprintFunctionLibrary.h"
#include "Global/GlobalHUD.h"
#include "Unreal_Project.h"
#include "Components/Button.h"

void UDragWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// TEXT("DragButton") 드래그 버튼이 안에 있어야만 한다.
	UButton* Button = Cast<UButton>(GetWidgetFromName(TEXT("DragButton")));

	// 버튼도 내가 만들어 버릴수 있다.
	// 그런대 배경이미지나 여러가지 구성요소도 신경써야 하는데 그건 유저(프로그래머)의 몫일 가능성이 높으므로
	// 이렇게 만든것.
	// CreateWidget

	if (nullptr == Button)
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (nullptr == Button)"), __FUNCTION__, __LINE__);
		return;
	}

	Button->OnPressed.Clear();
	Button->OnPressed.AddDynamic(this, &UDragWidget::DragStart);
	Button->OnReleased.Clear();
	Button->OnReleased.AddDynamic(this, &UDragWidget::DragEnd);
}

void UDragWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	DragUpdate();
}

void UDragWidget::SelectTopView()
{
	AGlobalHUD* HUD = UGlobalBlueprintFunctionLibrary::GetGlobalHUD(GetWorld());

	if (nullptr == HUD)
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (ItemMeshs.Num() <= static_cast<uint8>(_Slot))"), __FUNCTION__, __LINE__);
		return;
	}

	UCanvasPanelSlot* CSlot = Cast<UCanvasPanelSlot>(Slot);

	if (nullptr == CSlot)
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (ItemMeshs.Num() <= static_cast<uint8>(_Slot))"), __FUNCTION__, __LINE__);
		return;
	}

	//CSlot->SetZOrder(HUD->GetCurZOrder());
}

void UDragWidget::DragUpdate()
{
	if (false == DragCheck)
	{
		return;
	}

	FVector2D Result = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

	SetRenderTranslation(Result + DragOffset);
}

void UDragWidget::DragStart()
{
	DragCheck = true;

	FVector2D Result = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

	DragOffset = GetRenderTransform().Translation - Result;

	SelectTopView();
}

void UDragWidget::DragEnd()
{
	DragCheck = false;
}