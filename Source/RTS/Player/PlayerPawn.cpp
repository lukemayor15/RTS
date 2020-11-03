// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "RTS\Buildings\BaseBuilding.h"
#include "Kismet/GameplayStatics.h"
#include "RTS\Units\Unit.h"
#include "RTSPlayerController.h"
#include "RTS\Hud\RTSHUD.h"
#include "Kismet/KismetArrayLibrary.h"
#include "RTS\UserWidgets\CameraControl.h"




// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// set HudWidgetClass to the blueprint hud standardBuildingHud
	static ConstructorHelpers::FClassFinder<UUserWidget> BuildingHud(TEXT("/Game/UserWidgets/BuildingHud/StandardBuildingHud"));
	HUDWidgetClass = BuildingHud.Class;
}

//used to move the player/camera on the X axis
void APlayerPawn::MoveX(float AxisVal)
{
	FVector Pos = GetActorLocation();
	Pos.X += AxisVal;
	SetActorLocation(Pos);
}
//used to move the player/camera on the Y axis
void APlayerPawn::MoveY(float AxisVal)
{
	FVector Pos = GetActorLocation();
	Pos.Y -= AxisVal;
	SetActorLocation(Pos);
}
// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	//set current controller to the players controller
	CurrentController = static_cast<ARTSPlayerController*>(GetWorld()->GetFirstPlayerController());
	//Set hudfor secltion box to the the currentController Hud
	HudForSelectionBox = static_cast<ARTSHUD*>(CurrentController->GetHUD());
	//
	isBuilding = false;

	//Generate the default building hud
	HudForSelectionBox->CurrentWidget->GenereateButtons(HUDWidgetClass);

	//start values for the resoruces
	CurrentController->Wood += 600;
	CurrentController->Stone += 600;
	CurrentController->Gold += 600;
	CurrentController->MaxFood += 15;
	CurrentController->Food += 0;

	//updates the reosurces UI
	HudForSelectionBox->CurrentWidget->UpdateResoruceAmount();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if button is hover move on x axis
	if (ButtonHoveredX)
	{
		MoveX(AxisValueButtonX);
	}
	//if button is hover move on Y axis
	if (ButtonHoveredY)
	{
		MoveY(AxisValueButtonY);
	}
	//if mutliselect/ drawing the selection box update controller secondmouse position
	if (MultiSelect)
	{
		float MouseX, MouseY;
		CurrentController->GetMousePosition(MouseX, MouseY);
		CurrentController->SecondMousePos.X = MouseX;
		CurrentController->SecondMousePos.Y = MouseY;
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveX", this, &APlayerPawn::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &APlayerPawn::MoveY);
	PlayerInputComponent->BindAction("RightClick", IE_Pressed, this, &APlayerPawn::RightClickActions);
	PlayerInputComponent->BindAction("Select", IE_Pressed, this, &APlayerPawn::Select);
	PlayerInputComponent->BindAction("Select", IE_Released, this, &APlayerPawn::ReleasedLeftMouseButton);
}
//called by camera control, to let the player know we should be moving
//update buttonhoverdx to true and axisval
void APlayerPawn::SetButtonHoveredX(float AxisVal)
{
	ButtonHoveredX = true;
	AxisValueButtonX = AxisVal;
}
//called by camera control, to let the player know we should be moving
//update buttonhoverdy to true and axisval
void APlayerPawn::SetButtonHoveredY(float AxisVal)
{
	ButtonHoveredY = true;
	AxisValueButtonY = AxisVal;
}
//reset the hovering of buttons and axis value - called by camera control
void APlayerPawn::StopButtonHovered(float AxisVal)
{
	ButtonHoveredX = false;
	ButtonHoveredY = false;
	AxisValueButtonX = AxisVal;
	AxisValueButtonY = AxisVal;
}

//function to add units to the player controller unit list
void APlayerPawn::AddUnit(AUnit* Unit)
{
	//null pointer check
	if (Unit != nullptr)
	{	//check if unit is already in the list
		if (Unit->Selected != true)
		{	//null pointer check
			if (CurrentController != nullptr)
			{
				//empty current list
				ClearUnitsList();
				//add the selected unit to the list
				CurrentController->UnitList.Add(Unit);
				//set the unit selected bool to true
				Unit->Selected = true;
				//debug text
				UE_LOG(LogTemp, Warning, TEXT("United added"));

			}
		}
		else
		{
			
			UE_LOG(LogTemp, Warning, TEXT("Click on but already added"));

		}

	}

}

//
void APlayerPawn::RightClickActions()
{
	//null pointer check
	if (CurrentController != nullptr)
	{
		//if we have units in the player controller unit list we are wantinng to move them
		if (CurrentController->UnitList.Num() >= 0)
		{
			MoveUnit();
		}
		//if we are currently building and there is a building selected we want to destroy that building and reset to isbuilding to false
		if (CurrentController->BuildingList.Num() >= 0 && isBuilding)
		{

			CurrentController->BuildingList[0]->Destroy();
			CurrentController->BuildingList.Empty();
			isBuilding = false;
		}
	}

}

//Used to move the selecteed units to a position
void APlayerPawn::MoveUnit()
{
	//null pointer check
	if (CurrentController != nullptr)
	{
		//check if unitlist is not empty
		if (CurrentController->UnitList.Num() >= 0)
		{
			//loop through all units selected and set to moving and their target location
			for (int32 Index = 0; Index != CurrentController->UnitList.Num(); ++Index)
			{
				//nullpointer check
				if (CurrentController->UnitList[Index] != nullptr)
				{
					//Set move target to the mouse position
					CurrentController->UnitList[Index]->MoveTarget = GetMousePos();
					//set that they are moving
					CurrentController->UnitList[Index]->IsMoving = true;
					

				}

			}

		}
		//no units in unit list
		UE_LOG(LogTemp, Warning, TEXT("Is empty"));
	}

}
// minus the resource that are being used to build units/buildings
void APlayerPawn::MinusCost(int Gold, int Food, int Wood, int Stone)
{
	CurrentController->Gold -= Gold;
	CurrentController->Food += Food;
	CurrentController->Stone -= Stone;
	CurrentController->Wood -= Wood;

}

//When left clicked is press  this function is called to check
//what we are doing; building or unit selection
void APlayerPawn::Select()
{
	//are we building
	if (isBuilding)
	{	
		//check if building list is not empty
		if (CurrentController->BuildingList.Num() > 0)
		{
			//check if the building can be placed and is selected
			if (CurrentController->BuildingList[0]->CanBePlaced && !CurrentController->BuildingList[0]->Selected)
			{
				//set the building isPlaced to true,
				CurrentController->BuildingList[0]->IsPlaced = true;
				//take away the resoruce cost of this building, check to see if we have enough resouce is else where
				MinusCost(CurrentController->BuildingList[0]->GoldCost, CurrentController->BuildingList[0]->FoodCost, CurrentController->BuildingList[0]->WoodCost, CurrentController->BuildingList[0]->StoneCost);
				//Update the resource Hud
				HudForSelectionBox->CurrentWidget->UpdateResoruceAmount();
				//Building is placed so empty list and set isBuilding to false
				CurrentController->BuildingList.Empty();
				isBuilding = false;

				
			}
		}
	}
	// if we are not building and instead selecting units or buildings
	//Null pointer checks
	else if (HudForSelectionBox != nullptr || CurrentController != nullptr)
	{
		//var to get the hit results
		FHitResult Hit;
		//set local var to be used for the selection box drawings
		float MouseX, MouseY;
		//called is drawing (RTSHUD function)
		HudForSelectionBox->IsDrawing();
		//set multiselect to true, to know that we selecting
		MultiSelect = true;
		//get mouse position and set it for the first and second mouse posioton, used to find the diffrence betyween them to draw the selection rect
		CurrentController->GetMousePosition(MouseX, MouseY);
		CurrentController->FirstMousePos.X = MouseX;
		CurrentController->FirstMousePos.Y = MouseY;
		CurrentController->SecondMousePos.X = MouseX;
		CurrentController->SecondMousePos.Y = MouseY;
		//Check if unit is selected if so dont remove it from the unitlist
		if (CurrentController->GetHitResultUnderCursorForObjects(CurrentController->ObjectTypes, true, Hit))
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit"));

		}
		else
		{	//clearboth building and units list 
			ClearUnitsList();
			ClearBuildingsList();
			//update the hud to the default building widget as no other is selected
			HudForSelectionBox->CurrentWidget->GenereateButtons(HUDWidgetClass);

		}
	}

}
//clears the unit list array
void APlayerPawn::ClearUnitsList()
{
	//nullpointer check
	if (CurrentController != nullptr)
	{
		//if not empty
		if (CurrentController->UnitList.Num() > 0)
		{
			//loop through them and set selected to false
			for (int32 Index = 0; Index != CurrentController->UnitList.Num(); ++Index)
			{
				if (CurrentController->UnitList[Index] != nullptr)
				{
					CurrentController->UnitList[Index]->Selected = false;

				}

			}
			//empty the unitlist array
			CurrentController->UnitList.Empty();
		}
	}
}
//clear the building list array
void APlayerPawn::ClearBuildingsList()
{	
	//nullpointer check

	if (CurrentController != nullptr)
	{		
		//if not empty
		if (CurrentController->BuildingList.Num() >= 0)
		{
			//loop through them and set selected to false
			for (int32 Index = 0; Index != CurrentController->BuildingList.Num(); ++Index)
			{
				if (CurrentController->BuildingList[Index] != nullptr)
				{
					CurrentController->BuildingList[Index]->Selected = false;

				}

			}
			//clear building list
			CurrentController->BuildingList.Empty();
		}
	}
}
// function called when left mouse button is realsed
void APlayerPawn::ReleasedLeftMouseButton()
{
	//cnull pointer check
	if (HudForSelectionBox != nullptr)
	{
		//reset RTSHud/HudForSelectionBox and set multselect to false as no longer selecting units or buildings
		HudForSelectionBox->Reset();
		MultiSelect = false;
	}


}

//get the mouse position
FVector APlayerPawn::GetMousePos()
{
	FVector MousePos, MouseDic, NewLoc, NewDic;

	CurrentController->DeprojectMousePositionToWorld(MousePos, MouseDic);

	//sets mousePos.z to xero so hat all units and building that move or are spawned are on the same z posistion
	MousePos.Z = 0;

	return MousePos;
}