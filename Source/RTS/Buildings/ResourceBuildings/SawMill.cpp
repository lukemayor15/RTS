// Fill out your copyright notice in the Description page of Project Settings.


#include "SawMill.h"
#include "RTS\Resources\Wood.h"
#include "RTS\Player\RTSPlayerController.h"
#include "RTS\Player\PlayerPawn.h"
#include "RTS\Hud\RTSHud.h"
#include "RTS\UserWidgets\CameraControl.h"

bool ASawMill::CheckResourceType(TArray<AActor*>  OtherActor)
{
	if (OtherActor.Num() >= 0)
	{
		for (int i = 0; i != OtherActor.Num(); i++)
		{
			//check is overlapping an actor mesh
			TArray<UStaticMeshComponent*> Components;
			OtherActor[i]->GetComponents<UStaticMeshComponent>(Components);
			if (Components[0]->IsOverlappingActor(this))
			{
				UE_LOG(LogTemp, Warning, TEXT("Overlapping mesh"));
				return false;

			}
			//if not overlapping actor mesh check if we are overlapping the box collision for building
			if (OtherActor[i]->IsA(AWood::StaticClass()))
			{


				UE_LOG(LogTemp, Warning, TEXT("me nice"));
				return true;

			}
		}
	}
	return false;
}
void ASawMill::SetResourceIncreaseAmount()
{
	ResourceIncreaseAmount = 10;
}

void ASawMill::AddResource()
{
	PlayerAsPawn->CurrentController->Wood += ResourceIncreaseAmount;
	UE_LOG(LogTemp, Warning, TEXT("Wood, %d"), PlayerAsPawn->CurrentController->Wood);

	PlayerAsPawn->HudForSelectionBox->CurrentWidget->UpdateResoruceAmount();
	IncreaseDone = true;

}

void ASawMill::SetStartValues()
{
	WoodCost = 0;
	StoneCost = 0;
	FoodCost = 2;
	GoldCost = 150;
	Health = 200;
	MaxHealth = 200;
	BuildingName = FString(TEXT("SawMill"));
	IncreaseDone = false;

}
