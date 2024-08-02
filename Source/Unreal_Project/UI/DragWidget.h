// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PROJECT_API UDragWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void SelectTopView();

	UFUNCTION()
	void DragUpdate();

	UFUNCTION()
	void DragStart();

	UFUNCTION()
	void DragEnd();

private:
	bool DragCheck = false;
	FVector2D DragOffset;
};
