// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSHUD.generated.h"

/**
 *
 */
class AUnit;
UCLASS()
class RTS_API ARTSHUD : public AHUD
{
	GENERATED_BODY()
public:

	ARTSHUD();
	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	//Function that is called to draw the selection box
	void  DrawSelectionBox(TArray<AUnit*> UnitList, FVector2D FirstMousePos, FVector2D SecondMousePos);

	//Are we Drawing the selection Box
	void IsDrawing();
	//Rest values once we stoped drawings
	void Reset();

	//Bool to check if we are drawing the selection box
	UPROPERTY(EditAnywhere)
		uint32 Drawing : 1;
	//How many units are selected
	UPROPERTY(EditAnywhere)
		int UnitCount;
	//pointer to RTSPlayerController
	UPROPERTY(BlueprintReadOnly)
		class ARTSPlayerController* CurrentController;
	//Pointer to PlayerPawn
	UPROPERTY(BlueprintReadOnly)
		class APlayerPawn* PlayerPawn;
	//Pointer to CameraControl widget
	UPROPERTY(EditAnywhere, Category = "Move")
		class UCameraControl* CurrentWidget;



private:
	//Use to get blueprint class
	UPROPERTY(EditAnywhere, Category = "Move")
		TSubclassOf<class UUserWidget> HUDWidgetClass;




};
