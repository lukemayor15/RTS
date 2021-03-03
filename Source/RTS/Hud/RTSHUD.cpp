// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "RTS\Units/Unit.h"
#include "RTS\Player\PlayerPawn.h"
#include "RTS\Player\RTSPlayerController.h"
#include "RTS\UserWidgets\CameraControl.h"

ARTSHUD::ARTSHUD()
{
	//set HUdewidge calss to equal the camera control BP
	static ConstructorHelpers::FClassFinder<UUserWidget> Camera(TEXT("/Game/UserWidgets/CamereControlBP"));
	HUDWidgetClass = Camera.Class;

}

void ARTSHUD::BeginPlay()
{
	//Null pointer check
	if (HUDWidgetClass != nullptr)
	{
		//Creates the camera control widget
		CurrentWidget = CreateWidget<UCameraControl>(GetWorld(), HUDWidgetClass);

		//if not null add to the view point
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
	//set the current Controller to the player controller
	CurrentController = static_cast<ARTSPlayerController*>(GetWorld()->GetFirstPlayerController());
	//set player pawn to controled pawned
	PlayerPawn = static_cast<APlayerPawn*>(CurrentController->GetPawn());
	//unit count = 0;
	UnitCount = 0;




}

//used to draw a select box for the seelction of units and buildings
void ARTSHUD::DrawSelectionBox(TArray<AUnit*> SelectList, FVector2D FirstMousePos, FVector2D SecondMousePos)
{
	GetActorsInSelectionRectangle(FirstMousePos, SecondMousePos, SelectList, false);
	//get diffrence between firstmouse and second mouse and use that 

	//Draw the selection box
	DrawRect(FLinearColor(0.1f, 0.1f, 0.1f, 0.2f), FirstMousePos.X, FirstMousePos.Y, (SecondMousePos.X - FirstMousePos.X), (SecondMousePos.Y - FirstMousePos.Y));


	// if we are selecting one or more actor, debug messege
	if (SelectList.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Multi Hit"));

	}

	// checks if the  selectlist is != to the unitlist
	if (SelectList != CurrentController->UnitList)
	{
		//if they are not equal uupdate the unitlist
		CurrentController->UnitList = SelectList;
	}

}

void ARTSHUD::DrawHUD()
{
	Super::DrawHUD();
	//if we are drawing, left mouse button held down, call rawSelectionBox
	if (Drawing)
	{
		DrawSelectionBox(CurrentController->SelectList, CurrentController->FirstMousePos, CurrentController->SecondMousePos);

	}
}

//Set ISDrawing to true, on Mouse click
void ARTSHUD::IsDrawing()
{
	Drawing = true;
}
//Resets Drawing and unit count to 0 on left mouse relase
void ARTSHUD::Reset()
{
	Drawing = false;
	UnitCount = 0;

}

