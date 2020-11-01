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
	static ConstructorHelpers::FClassFinder<UUserWidget> Camera(TEXT("/Game/UserWidgets/CamereControlBP"));
	HUDWidgetClass = Camera.Class;

}

void ARTSHUD::BeginPlay()
{
	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UCameraControl>(GetWorld(), HUDWidgetClass);

		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}

	CurrentController = static_cast<ARTSPlayerController*>(GetWorld()->GetFirstPlayerController());
	PlayerPawn = static_cast<APlayerPawn*>(CurrentController->GetPawn());
	UnitCount = 0;




}

void ARTSHUD::DrawSelectionBox(TArray<AUnit*> SelectList, FVector2D FirstMousePos, FVector2D SecondMousePos)
{
	GetActorsInSelectionRectangle(FirstMousePos, SecondMousePos, SelectList);
	//get diffrence between firstmouse and second mouse and use that 

	DrawRect(FLinearColor(0.1f, 0.1f, 0.1f, 0.2f), FirstMousePos.X, FirstMousePos.Y, (SecondMousePos.X - FirstMousePos.X), (SecondMousePos.Y - FirstMousePos.Y));



	if (SelectList.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Multi Hit"));

	}

	if (SelectList != CurrentController->UnitList)
	{
		CurrentController->UnitList = SelectList;
	}

}

void ARTSHUD::DrawHUD()
{
	Super::DrawHUD();
	if (Drawing)
	{
		DrawSelectionBox(CurrentController->SelectList, CurrentController->FirstMousePos, CurrentController->SecondMousePos);

	}
}

void ARTSHUD::IsDrawing()
{
	Drawing = true;
}

void ARTSHUD::Reset()
{
	Drawing = false;
	UnitCount = 0;

}

