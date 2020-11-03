// Fill out your copyright notice in the Description page of Project Settings.


#include "Quarry.h"
#include "RTS\Resources\Stone.h"
#include "RTS\Player\RTSPlayerController.h"
#include "RTS\Player\PlayerPawn.h"
#include "RTS\Hud\RTSHud.h"
#include "RTS\UserWidgets\CameraControl.h"

//Check if we are overllaping the correct resource actor
bool AQuarry::CheckResourceType(TArray<AActor*> OtherActor)
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
			if (OtherActor[i]->IsA(AStone::StaticClass()))
			{


				UE_LOG(LogTemp, Warning, TEXT("Can Build"));
				return true;

			}

		}
	}
	return false;

}

//the resource increase amount added 
void AQuarry::SetResourceIncreaseAmount()
{
	ResourceIncreaseAmount = 8;
}

//is call on a timer, this adds and update the resouce amount in the player controller and UI
void AQuarry::AddResource()
{
	PlayerAsPawn->CurrentController->Stone += ResourceIncreaseAmount;
	UE_LOG(LogTemp, Warning, TEXT("Stone, %d"), PlayerAsPawn->CurrentController->Stone);

	PlayerAsPawn->HudForSelectionBox->CurrentWidget->UpdateResoruceAmount();
	IncreaseDone = true;

}

//Set the initial start values
void AQuarry::SetStartValues()
{
	WoodCost = 150;
	StoneCost = 0;
	FoodCost = 2;
	GoldCost = 100;
	Health = 150;
	MaxHealth = 150;
	BuildingName = FString(TEXT("Quarry"));

}