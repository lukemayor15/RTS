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

	void  DrawSelectionBox(TArray<AUnit*> UnitList, FVector2D FirstMousePos, FVector2D SecondMousePos);

	void IsDrawing();
	void Reset();

	UPROPERTY(EditAnywhere)
		uint32 Drawing : 1;

	UPROPERTY(EditAnywhere)
		int UnitCount;
	UPROPERTY(BlueprintReadOnly)
		class ARTSPlayerController* CurrentController;

	UPROPERTY(BlueprintReadOnly)
		class APlayerPawn* PlayerPawn;

	UPROPERTY(EditAnywhere, Category = "Move")
		class UCameraControl* CurrentWidget;



private:

	UPROPERTY(EditAnywhere, Category = "Move")
		TSubclassOf<class UUserWidget> HUDWidgetClass;




};
