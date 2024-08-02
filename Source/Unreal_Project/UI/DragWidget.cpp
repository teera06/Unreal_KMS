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

	// TEXT("DragButton") �巡�� ��ư�� �ȿ� �־�߸� �Ѵ�.
	UButton* Button = Cast<UButton>(GetWidgetFromName(TEXT("DragButton")));

	// ��ư�� ���� ����� ������ �ִ�.
	// �׷��� ����̹����� �������� ������ҵ� �Ű��� �ϴµ� �װ� ����(���α׷���)�� ���� ���ɼ��� �����Ƿ�
	// �̷��� �����.
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