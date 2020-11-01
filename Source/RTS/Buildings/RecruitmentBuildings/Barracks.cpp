// Fill out your copyright notice in the Description page of Project Settings.


#include "Barracks.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

ABarracks::ABarracks()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	ConstructorHelpers::FClassFinder<UUserWidget> HudClass(TEXT("/Game/UserWidgets/BuildingHud/Barracks"));
	if (HudClass.Class)
	{
		HUDWidgetClass = HudClass.Class;
		
	}
	
}

void ABarracks::SetStartValues()
{
	
	WoodCost = 100;
	StoneCost = 100;
	FoodCost = 3;
	GoldCost = 0;
	Health = 300;
	MaxHealth = 300;
	BuildingName = FString(TEXT("Barracks"));
}