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

	//Cheeck which button is hoverd.
	UPROPERTY(BlueprintReadOnly)
	uint32 ButtonHoveredX : 1;
	uint32 ButtonHoveredY : 1;
	//bool used to check if we are selecting units and should draw the selection hud
	uint32 MultiSelect : 1;
	//bool to check if the player is currently building
	UPROPERTY(BlueprintReadWrite)
	uint32 isBuilding : 1;
	//used to deterime is selected units should be attacking
	UPROPERTY(BlueprintReadWrite)
	uint32 IsAttacking : 1;

	//values set in cameracontroller, used to move player
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
	void MoveUnit(FHitResult RV_Hit);
	//on left mouse clicked this function is called to decide what to do
	void Select();
	//empty the array of player units, called on miss hit
	void ClearUnitsList();
	//empty the array of player buildings, called on miss hit
	void ClearBuildingsList();
	//check if left mouse button is released for selection rect
	void ReleasedLeftMouseButton();
	//get mouse pos
	UFUNCTION(BlueprintCallable)
	FVector GetMousePos();

	//used to minus the players resoucres when spent
	void MinusCost(int Gold, int Food, int Wood, int Stone);

	//use a different movemnt method for when the selected unit is attacking.
	void MoveToAttack(FHitResult RV_Hit);
	//
	TArray<FVector> GroupMovement(FHitResult RV_Hit, float RadiusChangeAmount, float SphereRadius, FVector Position, bool Attacking);

	TArray<FVector> GroupAttackMovement(FHitResult RV_Hit);

	class UFunctionLibrary* FunctionLibray;

};
