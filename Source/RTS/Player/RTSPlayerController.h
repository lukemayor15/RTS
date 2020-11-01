// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSPlayerController.generated.h"

/**
 *
 */
class AUnit;
class ABaseBuilding;

UCLASS()
class RTS_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:


	ARTSPlayerController();

public:

	UPROPERTY(BlueprintReadOnly)
		TArray<AUnit*> UnitList;
	UPROPERTY(BlueprintReadOnly)
		TArray<AUnit*> SelectList;

	UPROPERTY(BlueprintReadOnly)
		TArray< TEnumAsByte<EObjectTypeQuery> > ObjectTypes;

	UPROPERTY(BlueprintReadOnly)
		FVector2D FirstMousePos;

	UPROPERTY(BlueprintReadOnly)
		FVector2D SecondMousePos;

	UPROPERTY(BlueprintReadWrite)
		TArray<ABaseBuilding*> BuildingList;

	UPROPERTY(BlueprintReadOnly)
		int32 Gold;
	UPROPERTY(BlueprintReadOnly)
		int32 Wood;
	UPROPERTY(BlueprintReadOnly)
		int32 Food;
	UPROPERTY(BlueprintReadOnly)
		int32 MaxFood;
	UPROPERTY(BlueprintReadOnly)
		int32 Stone;



};


