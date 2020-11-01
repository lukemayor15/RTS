// Fill out your copyright notice in the Description page of Project Settings.


#include "House.h"
#include "RTS\Player\RTSPlayerController.h"
#include "RTS\Player\PlayerPawn.h"
#include "RTS\Hud\RTSHud.h"
#include "RTS\UserWidgets\CameraControl.h"

void AHouse::SetStartValues()
{
	WoodCost = 100;
	StoneCost = 0;
	FoodCost = 0;
	GoldCost = 0;
	BuildingName = FString(TEXT("House"));
	Health = 150;
	MaxHealth = 150;
	IncreaseDone = false;
}

void AHouse::SetResourceIncreaseAmount()
{
	ResourceIncreaseAmount = 4;
}

void AHouse::AddResource()
{
	if (!IncreaseDone)
	{
		PlayerAsPawn->CurrentController->MaxFood += ResourceIncreaseAmount;
		UE_LOG(LogTemp, Warning, TEXT("MaxFood, %d"), PlayerAsPawn->CurrentController->MaxFood);
		IncreaseDone = true;
		PlayerAsPawn->HudForSelectionBox->CurrentWidget->UpdateResoruceAmount();
	}
}
