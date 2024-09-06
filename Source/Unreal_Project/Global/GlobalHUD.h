// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/UIENum.h"
#include "GlobalHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECT_API AGlobalHUD : public AHUD
{
	GENERATED_BODY()
public:
#if WITH_EDITOR
	UFUNCTION(BlueprintCallable)
	void AddDebugString(FString _Text);
#endif

	UFUNCTION(BlueprintCallable)
	void UIOff(EPlayUIType _Type); // UI 끄기

	UFUNCTION(BlueprintCallable)
	void UIOn(EPlayUIType _Type); // UI 켜기

	UFUNCTION(BlueprintCallable)
	UUserWidget* GetUI(EPlayUIType _Type); // UI 가져오기

	UFUNCTION(BlueprintCallable)
	void UIVisibilitySwitch(EPlayUIType _Type); // ??


	UFUNCTION(BlueprintCallable)
	void UIVisibilitySwitchKey(FKey _Key);

	UFUNCTION(BlueprintCallable)
	void UISetVisibilityKey(FKey _Key, ESlateVisibility _Value);

	UFUNCTION(BlueprintCallable)
	void UISetVisibility(EPlayUIType _Type, ESlateVisibility _Value);

	/*UFUNCTION(BlueprintImplementableEvent, meta = (CallInEditor = true))
	void WidgetSizeAndPos(UUserWidget* _Widget, FAnchorData _Data);*/

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCurZOrder()
	{
		return ++CurZOrder;
	}

protected:
	void BeginPlay() override;

private:
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<EPlayUIType, UUserWidget*> Widgets;


	/*UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<EPlayUIType, FUICreateDataRow> WidgetDatas;*/

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))

	TMap<FKey, UUserWidget*> WidgetKeys;

	/*UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<FKey, FUICreateDataRow> WidgetKeyDatas;*/

	TArray<UUserWidget*> OpenWidget;

	int AllUIViewCount = 0;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int CurZOrder = 0;
};
