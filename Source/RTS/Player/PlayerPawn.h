// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

//USTRUCT(BlueprintType)
//struct FSpawnStore
//{
//	GENERATED_USTRUCT_BODY()
//public:
//	//sanitized movment input, ready to be used by game logic
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
//	class AUnit* SpawnUnit;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
//	FString UnitName;
//};


UCLASS()
class RTS_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();
	void MoveX(float AxisVal);
	void MoveY(float AxisVal);

	UPROPERTY(EditAnywhere, Category = "Hud")
		TSubclassOf<class UUserWidget> HUDWidgetClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Cheeck which button is over.
	UPROPERTY(BlueprintReadOnly)
	uint32 ButtonHoveredX : 1;
	uint32 ButtonHoveredY : 1;
	uint32 MultiSelect : 1;
	UPROPERTY(BlueprintReadWrite)
		uint32 isBuilding : 1;
	UPROPERTY(BlueprintReadWrite)
		uint32 BuildingSelected : 1;
	//values set incameracontroller
	UPROPERTY(BlueprintReadOnly)
		float AxisValueButtonX;
	float AxisValueButtonY;


	UPROPERTY(BlueprintReadOnly)
		class ARTSPlayerController* CurrentController;
	void SetButtonHoveredX(float AxisVal); // When button is hoverd set axis value and the corrpsonding button hover bool to true
	void SetButtonHoveredY(float AxisVal);// When button is hoverd set axis valueand the corrpsonding button hover bool to true
	void StopButtonHovered(float AxisVal);// When button is unhoverd set  set axis valueand the corrpsonding button hover bool to false

	//Hud pointer for drawing of selectable box
	UPROPERTY(BlueprintReadOnly)
		class ARTSHUD* HudForSelectionBox;

	UPROPERTY(BlueprintReadOnly)
		class UInputComponent* PlayerInputComponent1;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Add selected unit to array in RTScontroller
	void AddUnit(class AUnit* Unit);

	//used to detimermine what the right click should do 
	void RightClickActions();
	//Move select unit to location on tight mouse button
	void MoveUnit();

	void Select();
	//empty the array of player units, called on miss hit
	void ClearUnitsList();
	void ClearBuildingsList();
	//check if 
	void ReleasedLeftMouseButton();
	//get mouse pos
	UFUNCTION(BlueprintCallable)
		FVector GetMousePos();

	void MinusCost(int Gold, int Food, int Wood, int Stone);


};
