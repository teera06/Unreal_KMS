// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UI/UIENum.h"

#include "UIContext.generated.h"

class AGlobalHUD;

UCLASS(Blueprintable, ClassGroup = Component, BlueprintType, meta = (BlueprintSpawnableComponent))
class UNREAL_PROJECT_API UUIContext : public UActorComponent
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this component's properties
	UUIContext();

	UFUNCTION(BlueprintCallable)
	void UIVisibilitySwitch(EPlayUIType _Type);

	UFUNCTION(BlueprintCallable)
	void UIVisibilityOn(EPlayUIType _Type);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AGlobalHUD* PlayHUD=nullptr;
		
};
