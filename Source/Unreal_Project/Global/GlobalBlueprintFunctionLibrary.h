// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GlobalBlueprintFunctionLibrary.generated.h"

class AGlobalHUD;
class UGlobalGameInstance;
class AGloabalGameState;
/**
 * 
 */
UCLASS()
class UNREAL_PROJECT_API UGlobalBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
#if WITH_EDITOR
	UFUNCTION(BlueprintCallable)
	static void DebugTextPrint(UWorld* _World, FString Text);
#endif

	UFUNCTION(BlueprintPure, Category = "Game", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static AGlobalHUD* GetGlobalHUD(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Game", meta = (WorldContext = "WorldContextObject"))
	static UGlobalGameInstance* GetGlobalGameInstance(const UWorld* WorldContextObject);

	static AGloabalGameState* GetGloabalGameState(const UObject* WorldContextObject);

	template<typename EnumType>
	static void PushActor(const UObject* WorldContextObject, EnumType _GroupIndex, AActor* _Actor)
	{
		if (nullptr == WorldContextObject)
		{
			return;
		}

		PushActor(WorldContextObject, static_cast<uint8>(_GroupIndex), _Actor);
	}

	template<typename EnumType>
	static void PopActor(const UObject* WorldContextObject, EnumType _GroupIndex, AActor* _Actor)
	{
		if (nullptr == WorldContextObject)
		{
			return;
		}

		PopActor(WorldContextObject, static_cast<uint8>(_GroupIndex), _Actor);
	}


	UFUNCTION(BlueprintCallable, Category = "Game", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static void PushActor(const UObject* WorldContextObject, uint8 _GroupIndex, AActor* _Actor);

	UFUNCTION(BlueprintCallable, Category = "Game", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static void PopActor(const UObject* WorldContextObject, uint8 _GroupIndex, AActor* _Actor);

	/*UFUNCTION(BlueprintCallable, Category = "Game", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static bool PushGameItemToEmpty(const UObject* WorldContextObject, class ATPSGameItem* _Actor);*/

};
