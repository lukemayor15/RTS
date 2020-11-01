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
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	BoxCollision->bDynamicObstacle = true;
	StaticMesh->AttachTo(BoxCollision);
}

void ABaseBuilding::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GetOverlapedActors();
}

void ABaseBuilding::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//check to see if we still overlapping another compoment 
	GetOverlapedActors();


}

void ABaseBuilding::OnSelected(AActor* Target, FKey ButtonPressed)
{

	if (IsPlaced && !Selected)
	{

		AddToList();
	}
	else if (CanBePlaced)
	{
		IsPlaced = true;
		StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	}


}

void ABaseBuilding::SetStartValues()
{

}

void ABaseBuilding::AddToList()
{
	if (HUDWidgetClass != nullptr)
	{

		PlayerAsPawn->HudForSelectionBox->CurrentWidget->GenereateButtons(HUDWidgetClass);
	}

	if (!Selected)
	{
		PlayerAsPawn->ClearBuildingsList();
		PlayerAsPawn->CurrentController->BuildingList.Add(this);
	}

	PlayerAsPawn->HudForSelectionBox->CurrentWidget->UpdateSelectGrid();
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
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseBuilding::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ABaseBuilding::OnOverlapEnd);       // set up a notification for when this component overlaps something
	OnClicked.AddDynamic(this, &ABaseBuilding::OnSelected);

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