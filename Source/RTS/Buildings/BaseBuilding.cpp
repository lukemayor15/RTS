// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBuilding.h"
#include "RTS\Hud\RTSHUD.h"
#include "RTS\UserWidgets/CameraControl.h"
#include "Blueprint/UserWidget.h"
#include "BaseBuilding.h"
#include "RTS\Player\PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "RTS\Player\RTSPlayerController.h"





// Sets default values
ABaseBuilding::ABaseBuilding()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Create box collision compoment
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	//set cdd collision to true
	BoxCollision->bDynamicObstacle = true;
	//create a static mesh compoment
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->AttachTo(BoxCollision);
	//set ootComponentt 
	RootComponent = BoxCollision;
}

//Decide if we placing or selecting the building
void ABaseBuilding::OnSelected(AActor* Target, FKey ButtonPressed)
{
	// if already placed and is not selected add to list
	if (IsPlaced && !Selected)
	{

		AddToList();
	}
	//if can be placed and is not placed
	else if (CanBePlaced && !IsPlaced)
	{
		//Called placing function,this sets the building as placed.
		Placing();
	}


}

//Function that is override by children classes
void ABaseBuilding::SetStartValues()
{

}

//Creates the Widget for this class, and add it to BuildingList (the building tha are selected)
void ABaseBuilding::AddToList()
{
	// Check for null pointer
	if (HUDWidgetClass != nullptr)
	{
		//create the buttons base on the building when selected
		PlayerAsPawn->HudForSelectionBox->CurrentWidget->GenereateButtons(HUDWidgetClass);
	}
	//if the building is not already in the building list, 
	if (!Selected)
	{
		//clear the buidling list
		PlayerAsPawn->ClearBuildingsList();
		// add this building to the building list
		PlayerAsPawn->CurrentController->BuildingList.Add(this);
	}

	//Updates the selection grid
	PlayerAsPawn->HudForSelectionBox->CurrentWidget->UpdateSelectGrid();
	//isbuildig and select to true
	PlayerAsPawn->isBuilding = true;
	Selected = true;
}



// Called when the game starts or when spawned
void ABaseBuilding::BeginPlay()
{
	Super::BeginPlay();
	//get the player object
	PlayerAsPawn = static_cast<APlayerPawn*>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//Initilate bool values set to false
	IsPlaced = false;
	Selected = false;
	CanBePlaced = false;
	// set up OnCliked to this building, when the building left clicked on call the OnSelect function
	OnClicked.AddDynamic(this, &ABaseBuilding::OnSelected);									  //set up a Oncliked to call the OnSelected function to determine if building or slected
	//Check for overlapping actors
	GetOverlapedActors();
	//Set the start values of building for example health and wood cost
	SetStartValues();

	//Create a timer instead of using event tick to check for overlapped actors
	GetWorldTimerManager().SetTimer(BuildingMemberTimerHandle, this, &ABaseBuilding::BuildingTimerFunction, 0.33f, true, 0.0f);
}

void ABaseBuilding::BuildingTimerFunction()
{
	//Checks for overlaped actors
	GetOverlapedActors();
}

//change values so the building is placed/built
void ABaseBuilding::Placing()
{
	//change IsPlaced to true and change collision of the static mesh to block
	IsPlaced = true;
	StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	//Clear the building timer as it already built so dont need to check .
	GetWorldTimerManager().ClearTimer(BuildingMemberTimerHandle);
}

// Called every frame
void ABaseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Updates the position of the actor same as the mouse while it isnt placed/built
	if (!IsPlaced)
	{
		SetActorLocation(PlayerAsPawn->GetMousePos());
	}
}

// Called to bind functionality to input
void ABaseBuilding::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ABaseBuilding::GetOverlapedActors()
{
	//create an Actor array and set it to the overlaped actors
	TArray<AActor*> OverlapedActors;
	GetOverlappingActors(OverlapedActors, TSubclassOf <AActor>());

	// cgeck for any overlaping actor
	if (OverlapedActors.Num() == 0)
	{
		// no overlap actor set can be place to true
		CanBePlaced = true;
		UE_LOG(LogTemp, Warning, TEXT(" No overlaps"));

	}
	else
	{ 
		//otherwise set can be placed to be false
		CanBePlaced = false;
		UE_LOG(LogTemp, Warning, TEXT(" Overlaps"));


	}
}