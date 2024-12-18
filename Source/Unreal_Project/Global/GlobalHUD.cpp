// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GlobalHUD.h"
#include "Global/GlobalBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Unreal_Project.h"
#include "Blueprint/WidgetTree.h"
#include "Global/GlobalGameInstance.h"
#include "UI/DT/UICreateDataRow.h"

void AGlobalHUD::AddDebugString(FString _Text)
{
	/*if (nullptr == DebugWidget)
	{
		return;
	}

	DebugWidget->AddDebugString(_Text);*/
}

void AGlobalHUD::UIOff(EPlayUIType _Type)
{
	UISetVisibility(_Type, ESlateVisibility::Hidden);
}

void AGlobalHUD::UIOn(EPlayUIType _Type)
{
	UISetVisibility(_Type, ESlateVisibility::Visible); // 인번토리 처음 킬때 여기로 넘어옴
}

UUserWidget* AGlobalHUD::GetUI(EPlayUIType _Type)
{
	UUserWidget** WidgetPtr = Widgets.Find(_Type);
	return *WidgetPtr;
}

void AGlobalHUD::UIVisibilitySwitch(EPlayUIType _Type)
{
	UUserWidget** WidgetPtr = Widgets.Find(_Type);
	UUserWidget* Widget = *WidgetPtr;

	if (ESlateVisibility::Visible == Widget->GetVisibility())
	{
		UIOff(_Type);
	}
	else if (ESlateVisibility::Hidden == Widget->GetVisibility())
	{
		UIOn(_Type);
	}
}

void AGlobalHUD::UIVisibilitySwitchKey(FKey _Key)
{
	// UI 닫을 때
	if (true == WidgetKeys.IsEmpty())
	{
		return;
	}

	if (false == WidgetKeys.Contains(_Key))
	{
		return;
	}


	UUserWidget** WidgetPtr = WidgetKeys.Find(_Key); // 등록 해둔 키로 위젯을 찾음
	UUserWidget* Widget = *WidgetPtr;

	if (ESlateVisibility::Visible == Widget->GetVisibility())
	{
		UISetVisibilityKey(_Key, ESlateVisibility::Hidden);
	}
	else if (ESlateVisibility::Hidden == Widget->GetVisibility())
	{
		UISetVisibilityKey(_Key, ESlateVisibility::Visible);
	}
}

void AGlobalHUD::UISetVisibilityKey(FKey _Key, ESlateVisibility _Value)
{
	UUserWidget** WidgetPtr = WidgetKeys.Find(_Key); // UI 닫을 때는 여기로 넘어옴
	UUserWidget* Widget = *WidgetPtr;

	if (nullptr == Widget)
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (nullptr == Widget)"), __FUNCTION__, __LINE__);
	}

	if (_Value == ESlateVisibility::Visible)
	{
		FUICreateDataRow* DataPtr = WidgetKeyDatas.Find(_Key);
		if (DataPtr->OpenMode == EUIInputMode::UIOnly)
		{
			APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

			FInputModeUIOnly Option;
			Option.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			Controller->SetInputMode(Option);
			Controller->bShowMouseCursor = true;
		}

		OpenWidget.Add(Widget);
		Widget->SetFocus();
		++AllUIViewCount;
	}
	else if (_Value == ESlateVisibility::Hidden)
	{
		--AllUIViewCount;
		OpenWidget.Remove(Widget);

		if (0 == AllUIViewCount)
		{
			APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			FInputModeGameOnly Option;
			Option.SetConsumeCaptureMouseDown(true);
			Controller->SetInputMode(Option);
			Controller->bShowMouseCursor = false;
		}
		else
		{
			OpenWidget[OpenWidget.Num() - 1]->SetFocus();
		}
	}

	Widget->SetVisibility(_Value);
}

// 여기가 인벤토리 키 눌렀을때 오는 함수
void AGlobalHUD::UISetVisibility(EPlayUIType _Type, ESlateVisibility _Value)
{
	UUserWidget** WidgetPtr = Widgets.Find(_Type); // UI 타입 (인벤토리냐, 장비창이냐) Map으로 구분
	UUserWidget* Widget = *WidgetPtr; // 찾은 UI 위젯 값

	if (nullptr == Widget)
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (nullptr == Widget)"), __FUNCTION__, __LINE__);
	}

	if (_Value == ESlateVisibility::Visible)
	{
		FUICreateDataRow* DataPtr = WidgetDatas.Find(_Type);
		
		if (DataPtr->OpenMode == EUIInputMode::UIOnly)
		{
			APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			
			FInputModeUIOnly UIOnly;
			UIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			//UIOnly.SetWidgetToFocus(nullptr);
			Controller->SetInputMode(UIOnly);
			Controller->bShowMouseCursor = true;
		}

		OpenWidget.Add(Widget);
		Widget->SetFocus();
		++AllUIViewCount;
	}
	else if (_Value == ESlateVisibility::Hidden)
	{
		--AllUIViewCount;
		OpenWidget.Remove(Widget);

		if (0 == AllUIViewCount)
		{
			APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			FInputModeGameOnly Option;
			Option.SetConsumeCaptureMouseDown(true);
			Controller->SetInputMode(Option);
			Controller->bShowMouseCursor = false;
		}
		else
		{
			OpenWidget[OpenWidget.Num() - 1]->SetFocus();
		}
	}

	Widget->SetVisibility(_Value);
}


void AGlobalHUD::BeginPlay()
{
	Super::BeginPlay();


	UGlobalGameInstance* Inst = UGlobalBlueprintFunctionLibrary::GetGlobalGameInstance(GetWorld());

	TMap<FString, FUICreateDataRow>& AllUI = Inst->GetUIPlayerWigets();

	UEnum* Enum = StaticEnum<EPlayUIType>();
	
	TSubclassOf<UUserWidget> MainWidgetClass = LoadClass<UUserWidget>(NULL, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Play/BP_MainPlayWidget.BP_MainPlayWidget_C'"));

	UUserWidget* MainWidget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass);
	MainWidget->AddToViewport();

	UWidget* ParentWidget = MainWidget->GetWidgetFromName(TEXT("MainPenal"));
	UPanelWidget* PanelWidget = Cast<UPanelWidget>(ParentWidget);

	//// 애초에 빌드할때는 
	for (TPair<FString, FUICreateDataRow> Pair : AllUI)
	{
		FUICreateDataRow& Data = Pair.Value;
		
		UUserWidget* Widget = MainWidget->WidgetTree->ConstructWidget<UUserWidget>(Data.Object, *Pair.Key);
	//	// 자식이니까 해줄필요가 없다.
	//	// 부모가 한번 이미 했다.
	// 
	    //Widget->AddToViewport();
		
		EPlayUIType Type = static_cast<EPlayUIType>(Enum->GetValueByName(*Pair.Key));
		
		Widgets.Add(Type, Widget);
		WidgetDatas.Add(Type, Data);
		
		if (Data.Key != FKey())
		{
			WidgetKeyDatas.Add(Data.Key, Data);
			WidgetKeys.Add(Data.Key, Widget);
		}
		
		PanelWidget->AddChild(Widget);
		WidgetSizeAndPos(Widget, Data.InitScaleToPos);

		if (false == Data.StartOn)
		{
			Widget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

