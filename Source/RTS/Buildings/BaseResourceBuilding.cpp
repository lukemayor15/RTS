// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseResourceBuilding.h"
#include "RTS\Player/PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "RTS\Hud/RTSHUD.h"
#include "RTS\Player/RTSPlayerController.h"
#include "RTS\UserWidgets/CameraControl.h"



void ABaseResourceBuilding::BeginPlay()
{
	Super::BeginPlay();
	//get the player pawn
	PlayerAsPawn = static_cast<APlayerPawn*>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//set inital bools to false
	IsPlaced = false;
	Selected = false;
	CanBePlaced = false;
	IncreaseDone = false;
      // set up a notification for when this component overlaps something
	OnClicked.AddDynamic(this, &ABaseBuilding::OnSelected);
	//BoxCollision->bDynamicObstacle = false;
	//the default increase for adding resources
	IncreaseTime = 10.0f;
	//set the resource increase amount
	SetResourceIncreaseAmount();
	//Check for overlaped actors
	GetOverlapedActors();

	//Create a timer instead of using event tick to check for overlapped actors
	GetWorldTimerManager().SetTimer(BuildingMemberTimerHandle, this, &ABaseBuilding::BuildingTimerFunction, 0.33f, true, 0.0f);

}

bool ABaseResourceBuilding::CheckResourceType(TArray<AActor*>  OtherActor)
{
	//Check if there any overlapped actors
	if (OtherActor.Num() == 0)
	{
		// if no actor can be place else cant be
		UE_LOG(LogTemp, Warning, TEXT("Can Build"));
		return true;
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cant"));
		return false;
	}
	
}

//Decide if we placing or selecting the building
void ABaseResourceBuilding::OnSelected(AActor* Target, FKey ButtonPressed)
{
	// if already placed and is not selected add to list

	if (IsPlaced && !Selected)
	{
		AddToList();
	}
	else if (CanBePlaced && IncreaseDone == false)
	{
		//Called placing function,this sets the building as placed.

		Placing();
		
	}

}
//change values so the building is placed/built
void ABaseResourceBuilding::Placing()
{
	//change the collision so that it other building and units and overlap it
	StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	BoxCollision->bDynamicObstacle = true;
	//Clear time to check for overllaping actors as it is no longer needed
	GetWorldTimerManager().ClearTimer(BuildingMemberTimerHandle);
	// start the resource timer, peridocally increase the player resource
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ABaseResourceBuilding::AddResource, IncreaseTime, true, 0.0f);
}
//Checl for overllapinf actors
void ABaseResourceBuilding::GetOverlapedActors()
{
	TArray<AActor*> OverlapedActors;
	GetOverlappingActors(OverlapedActors, TSubclassOf <AActor>());
	//calls check reosurce type if return true can be place
	if (CheckResourceType(OverlapedActors))
	{
		CanBePlaced = true;

	}
	else
	{
		// the resource building cant be placed
		CanBePlaced = false;
	}
}

void ABaseResourceBuilding::AddResource()
{
	//Gets Overrided based on building type
}

void ABaseResourceBuilding::SetResourceIncreaseAmount()
{
	//Gets Overrided based on building type
}
