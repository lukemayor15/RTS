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
	//array that the units that are selected
	UPROPERTY(BlueprintReadOnly)
	TArray<AUnit*> UnitList;
	//array that holds the units that are selected by the selection rect, then is checked again the UnitList for changes,
	UPROPERTY(BlueprintReadOnly)
	TArray<AUnit*> SelectList;

	//array of units that are attacking without a command
	UPROPERTY(BlueprintReadOnly)
	TArray<AUnit*> AttackUnitList;
	//an Object array to determine which objects can be selected
	UPROPERTY(BlueprintReadOnly)
	TArray< TEnumAsByte<EObjectTypeQuery> > ObjectTypes;

	//first mouse poisiton used in drawing the selection rect
	UPROPERTY(BlueprintReadOnly)
		FVector2D FirstMousePos;
	//second mouse poisiton used in drawing the selection rect
	UPROPERTY(BlueprintReadOnly)
	FVector2D SecondMousePos;
	//array that holds the buildings that are selected
	UPROPERTY(BlueprintReadWrite)
	TArray<ABaseBuilding*> BuildingList;
	//The player resoruce varaibles
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


