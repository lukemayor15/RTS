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

	static ConstructorHelpers::FClassFinder<UUserWidget> BuildingHud(TEXT("/Game/UserWidgets/BuildingHud/StandardBuildingHud"));
	HUDWidgetClass = BuildingHud.Class;
}

void APlayerPawn::MoveX(float AxisVal)
{
	FVector Pos = GetActorLocation();
	Pos.X += AxisVal;
	SetActorLocation(Pos);
}

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
	CurrentController = static_cast<ARTSPlayerController*>(GetWorld()->GetFirstPlayerController());
	HudForSelectionBox = static_cast<ARTSHUD*>(CurrentController->GetHUD());
	isBuilding = false;

	HudForSelectionBox->CurrentWidget->GenereateButtons(HUDWidgetClass);

	CurrentController->Wood += 600;
	CurrentController->Stone += 600;
	CurrentController->Gold += 600;
	CurrentController->MaxFood += 15;
	CurrentController->Food += 0;

	HudForSelectionBox->CurrentWidget->UpdateResoruceAmount();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ButtonHoveredX)
	{
		MoveX(AxisValueButtonX);
	}
	if (ButtonHoveredY)
	{
		MoveY(AxisValueButtonY);
	}
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
void APlayerPawn::SetButtonHoveredX(float AxisVal)
{
	ButtonHoveredX = true;
	AxisValueButtonX = AxisVal;
}
void APlayerPawn::SetButtonHoveredY(float AxisVal)
{
	ButtonHoveredY = true;
	AxisValueButtonY = AxisVal;
}
void APlayerPawn::StopButtonHovered(float AxisVal)
{
	ButtonHoveredX = false;
	ButtonHoveredY = false;
	AxisValueButtonX = AxisVal;
	AxisValueButtonY = AxisVal;
}

void APlayerPawn::AddUnit(AUnit* Unit)
{

	if (Unit != nullptr)
	{
		if (Unit->Selected != true)
		{
			if (CurrentController != nullptr)
			{
				ClearUnitsList();
				CurrentController->UnitList.Add(Unit);
				Unit->Selected = true;
				UE_LOG(LogTemp, Warning, TEXT("United added"));

			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Click on but already added"));

		}

	}

}


void APlayerPawn::RightClickActions()
{
	if (CurrentController != nullptr)
	{
		if (CurrentController->UnitList.Num() >= 0)
		{
			MoveUnit();
		}
		if (CurrentController->BuildingList.Num() >= 0 && isBuilding)
		{

			CurrentController->BuildingList[0]->Destroy();
			CurrentController->BuildingList.Empty();
			isBuilding = false;
		}
	}

}

void APlayerPawn::MoveUnit()
{
	if (CurrentController != nullptr)
	{
		if (CurrentController->UnitList.Num() >= 0)
		{

			for (int32 Index = 0; Index != CurrentController->UnitList.Num(); ++Index)
			{
				if (CurrentController->UnitList[Index] != nullptr)
				{
					CurrentController->UnitList[Index]->MoveTarget = GetMousePos();
					CurrentController->UnitList[Index]->IsMoving = true;
					

				}

			}

		}

		UE_LOG(LogTemp, Warning, TEXT("Is empty"));
	}

}
void APlayerPawn::MinusCost(int Gold, int Food, int Wood, int Stone)
{
	CurrentController->Gold -= Gold;
	CurrentController->Food += Food;
	CurrentController->Stone -= Stone;
	CurrentController->Wood -= Wood;

}

void APlayerPawn::Select()
{
	if (isBuilding)
	{
		if (CurrentController->BuildingList.Num() > 0)
		{
			if (CurrentController->BuildingList[0]->CanBePlaced && !CurrentController->BuildingList[0]->Selected)
			{
				
				CurrentController->BuildingList[0]->IsPlaced = true;
				MinusCost(CurrentController->BuildingList[0]->GoldCost, CurrentController->BuildingList[0]->FoodCost, CurrentController->BuildingList[0]->WoodCost, CurrentController->BuildingList[0]->StoneCost);
				HudForSelectionBox->CurrentWidget->UpdateResoruceAmount();
				CurrentController->BuildingList.Empty();
				isBuilding = false;

				
			}
		}
	}
	else if (HudForSelectionBox != nullptr || CurrentController != nullptr)
	{
		FHitResult Hit;
		float MouseX, MouseY;
		HudForSelectionBox->IsDrawing();
		MultiSelect = true;
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
		{
			ClearUnitsList();
			ClearBuildingsList();
			HudForSelectionBox->CurrentWidget->GenereateButtons(HUDWidgetClass);

		}



	}

}

void APlayerPawn::ClearUnitsList()
{
	if (CurrentController != nullptr)
	{
		if (CurrentController->UnitList.Num() > 0)
		{
			for (int32 Index = 0; Index != CurrentController->UnitList.Num(); ++Index)
			{
				if (CurrentController->UnitList[Index] != nullptr)
				{
					CurrentController->UnitList[Index]->Selected = false;

				}

			}
			CurrentController->UnitList.Empty();
		}
	}
}

void APlayerPawn::ClearBuildingsList()
{
	if (CurrentController != nullptr)
	{
		if (CurrentController->BuildingList.Num() >= 0)
		{
			for (int32 Index = 0; Index != CurrentController->BuildingList.Num(); ++Index)
			{
				if (CurrentController->BuildingList[Index] != nullptr)
				{
					CurrentController->BuildingList[Index]->Selected = false;

				}

			}
			CurrentController->BuildingList.Empty();
		}
	}
}

void APlayerPawn::ReleasedLeftMouseButton()
{
	if (HudForSelectionBox != nullptr)
	{
		HudForSelectionBox->Reset();
		MultiSelect = false;
	}


}

FVector APlayerPawn::GetMousePos()
{
	FVector MousePos, MouseDic, NewLoc, NewDic;

	CurrentController->DeprojectMousePositionToWorld(MousePos, MouseDic);

	MousePos.Z = 0;

	return MousePos;
}