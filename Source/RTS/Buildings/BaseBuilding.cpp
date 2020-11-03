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

//Called when a compoment overlap begins
void ABaseBuilding::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
		//check to see if we still overlapping another compoment 

	GetOverlapedActors();
}
//Called when a compoment  overlap ends 
void ABaseBuilding::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//check to see if we still overlapping another compoment 
	GetOverlapedActors();


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
		//Chnage IsPlaced to true and change collision of the static mesh to block
		IsPlaced = true;
		StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
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

	
	PlayerAsPawn = static_cast<APlayerPawn*>(GetWorld()->GetFirstPlayerController()->GetPawn());
	IsPlaced = false;
	Selected = false;
	CanBePlaced = false;
	BoxCollision->GetGenerateOverlapEvents();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseBuilding::OnOverlapBegin);	  // set up a notification for when this component overlaps something
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ABaseBuilding::OnOverlapEnd);       // set up a notification for when this component overlaps something
	OnClicked.AddDynamic(this, &ABaseBuilding::OnSelected);									  //set up a Oncliked to call the OnSelected function to determine if building or slected

	GetOverlapedActors();
	SetStartValues();
}

// Called every frame
void ABaseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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


	if (OverlapedActors.Num() == 0)
	{
		CanBePlaced = true;
		UE_LOG(LogTemp, Warning, TEXT(" No overlaps"));

	}
	else
	{
		CanBePlaced = false;
		UE_LOG(LogTemp, Warning, TEXT(" Overlaps"));


	}
}