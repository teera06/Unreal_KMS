// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GlobalHUD.h"
#include "Global/GlobalBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Unreal_Project.h"
#include "Blueprint/WidgetTree.h"

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
	/*UISetVisibility(_Type, ESlateVisibility::Hidden);*/
}

void AGlobalHUD::UIOn(EPlayUIType _Type)
{
	/*UISetVisibility(_Type, ESlateVisibility::Visible);*/
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
	if (true == WidgetKeys.IsEmpty())
	{
		return;
	}

	if (false == WidgetKeys.Contains(_Key))
	{
		return;
	}


	UUserWidget** WidgetPtr = WidgetKeys.Find(_Key);
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
	UUserWidget** WidgetPtr = WidgetKeys.Find(_Key);
	UUserWidget* Widget = *WidgetPtr;

	if (nullptr == Widget)
	{
		UE_LOG(MyLog, Fatal, TEXT("%S(%u)> if (nullptr == Widget)"), __FUNCTION__, __LINE__);
	}

	if (_Value == ESlateVisibility::Visible)
	{
		/*FUICreateDataRow* DataPtr = WidgetKeyDatas.Find(_Key);
		if (DataPtr->OpenMode == ETPSUIInputMode::UIOnly)
		{
			APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

			FInputModeUIOnly Option;
			Option.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			Controller->SetInputMode(Option);
			Controller->bShowMouseCursor = true;
		}

		OpenWidget.Add(Widget);
		Widget->SetFocus();*/
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


	//UGIMATGameInstance* Inst = UGlobalBlueprintFunctionLibrary::GetGIMATGameInstance(GetWorld());

	//TMap<FString, FUICreateDataRow>& AllUI = Inst->GetTPSPlayWidgets();

	//UEnum* Enum = StaticEnum<ETPSPlayUIType>();

	//TSubclassOf<UUserWidget> MainWidgetClass = LoadClass<UUserWidget>(NULL, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/TPS/Play/UI/BP_MainPlayWidget.BP_MainPlayWidget_C'"));

	//UUserWidget* MainWidget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass);
	//MainWidget->AddToViewport();

	//UWidget* ParentWidget = MainWidget->GetWidgetFromName(TEXT("MainPenal"));
	//UPanelWidget* PanelWidget = Cast<UPanelWidget>(ParentWidget);

	//// 애초에 빌드할때는 
	//for (TPair<FString, FUICreateDataRow> Pair : AllUI)
	//{
	//	FUICreateDataRow& Data = Pair.Value;



	//	UUserWidget* Widget = MainWidget->WidgetTree->ConstructWidget<UUserWidget>(Data.Object, *Pair.Key);
	//	// 자식이니까 해줄필요가 없다.
	//	// 부모가 한번 이미 했다.
	//	// Widget->AddToViewport();

	//	ETPSPlayUIType Type = static_cast<ETPSPlayUIType>(Enum->GetValueByName(*Pair.Key));

	//	Widgets.Add(Type, Widget);
	//	WidgetDatas.Add(Type, Data);

	//	if (Data.Key != FKey())
	//	{
	//		WidgetKeyDatas.Add(Data.Key, Data);
	//		WidgetKeys.Add(Data.Key, Widget);
	//	}

	//	PanelWidget->AddChild(Widget);
	//	WidgetSizeAndPos(Widget, Data.InitScaleToPos);

	//	if (false == Data.StartOn)
	//	{
	//		Widget->SetVisibility(ESlateVisibility::Hidden);
	//	}
	//}
}

