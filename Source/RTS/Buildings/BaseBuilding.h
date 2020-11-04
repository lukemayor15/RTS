// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseBuilding.generated.h"

UCLASS()
class RTS_API ABaseBuilding : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties


	ABaseBuilding();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	TSubclassOf<class UUserWidget> HUDWidgetClass;
	

	UPROPERTY(BlueprintReadOnly)
	class APlayerPawn* PlayerAsPawn;
	//bools to determine, if is placed, CanBePlaced,is  selected
	UPROPERTY(BlueprintReadWrite)
	uint32 IsPlaced : 1;
	UPROPERTY(BlueprintReadWrite)
	uint32 CanBePlaced : 1;
	UPROPERTY(BlueprintReadWrite)
	uint32 Selected : 1;

	
	//Box compnonet pointer
	UPROPERTY(VisibleAnywhere, Category = "Switch Components")
	class UBoxComponent* BoxCollision;
	//static mesh pointer
	UPROPERTY(VisibleAnywhere, Category = "Static Mesh")
	class UStaticMeshComponent* StaticMesh;

	// Unit pointer
	UPROPERTY(BlueprintReadWrite, Category = "Switch Components")
	class AUnit* TestUnit;
	//Widget pointer
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = HUD)
	class UWidget* Widget;
	//

	//Function to decide what to do when selected based on if it is placed or not
	UFUNCTION()
	virtual void OnSelected(AActor* Target, FKey ButtonPressed);
	// use to set the intial start values
	UFUNCTION()
	virtual void SetStartValues();
	//function to add buildings to player controler building list
	UFUNCTION()
	void AddToList();

	/* Handle to manage the timer */
	FTimerHandle MemberTimerHandle;
	//Standard Values
	UPROPERTY(BlueprintReadWrite)
	int32 Health;
	UPROPERTY(BlueprintReadWrite)
	int32 MaxHealth;
	UPROPERTY(BlueprintReadWrite, Category = "Cost")
	int WoodCost;
	UPROPERTY(BlueprintReadWrite, Category = "Cost")
	int GoldCost;
	UPROPERTY(BlueprintReadWrite, Category = "Cost")
	int FoodCost;
	UPROPERTY(BlueprintReadWrite, Category = "Cost")
	int StoneCost;
	UPROPERTY(BlueprintReadWrite, Category = "Name")
	FString BuildingName;

	//Blueprint callable function to get the Overlaped actors
	UFUNCTION(Blueprintcallable)
	virtual void GetOverlapedActors();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




};
