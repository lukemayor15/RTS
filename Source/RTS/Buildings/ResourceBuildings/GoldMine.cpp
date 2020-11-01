// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldMine.h"
#include "RTS\Resources\Gold.h"
#include "RTS\Player\RTSPlayerController.h"
#include "RTS\Player\PlayerPawn.h"
#include "RTS\Hud\RTSHud.h"
#include "RTS\UserWidgets\CameraControl.h"

bool AGoldMine::CheckResourceType(TArray<AActor*>  OtherActor)
{
	if (OtherActor.Num() >= 0)
	{
		for (int i = 0; i != OtherActor.Num(); i++)
		{
			//check is overlapping an actor mAesh
			TArray<UStaticMeshComponent*> Components;
			OtherActor[i]->GetComponents<UStaticMeshComponent>(Components);
			if (Components[0]->IsOverlappingActor(this))
			{
				UE_LOG(LogTemp, Warning, TEXT("Overlapping mesh"));
				return false;

			}
			//if not overlapping actor mesh check if we are overlapping the box collision for building
			if (OtherActor[i]->IsA(AGold::StaticClass()))
			{


				UE_LOG(LogTemp, Warning, TEXT("me nice"));
				return true;

			}
		}
	}
	return false;
}
void AGoldMine::SetResourceIncreaseAmount()
{
	ResourceIncreaseAmount = 12;
}

void AGoldMine::AddResource()
{
	PlayerAsPawn->CurrentController->Gold += ResourceIncreaseAmount;
	UE_LOG(LogTemp, Warning, TEXT("Gold, %d"), PlayerAsPawn->CurrentController->Gold);
	PlayerAsPawn->HudForSelectionBox->CurrentWidget->UpdateResoruceAmount();
	IncreaseDone = true;

}

void AGoldMine::SetStartValues()
{
	WoodCost = 100;
	StoneCost = 100;
	FoodCost = 2;
	GoldCost = 0;
	Health = 150;
	MaxHealth = 150;
	BuildingName = FString(TEXT("Gold Mine"));
}
