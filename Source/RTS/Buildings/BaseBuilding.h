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

	UPROPERTY(BlueprintReadWrite)
	uint32 IsPlaced : 1;
	UPROPERTY(BlueprintReadWrite)
	uint32 CanBePlaced : 1;
	UPROPERTY(BlueprintReadWrite)
	uint32 Selected : 1;

	

	UPROPERTY(VisibleAnywhere, Category = "Switch Components")
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, Category = "Static Mesh")
	class UStaticMeshComponent* StaticMesh;


	UPROPERTY(BlueprintReadWrite, Category = "Switch Components")
	class AUnit* TestUnit;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = HUD)
	class UWidget* Widget;

	UPROPERTY(BlueprintReadWrite)
	int32 Health;
	UPROPERTY(BlueprintReadWrite)
	int32 MaxHealth;
	/** called when something enters the boxomponent */
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** called when something leaves the boxomponent component */
	UFUNCTION()
	virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	virtual void OnSelected(AActor* Target, FKey ButtonPressed);

	UFUNCTION()
	virtual void SetStartValues();

	UFUNCTION()
	void AddToList();

	/* Handle to manage the timer */
	FTimerHandle MemberTimerHandle;

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
	UFUNCTION(Blueprintcallable)
	virtual void GetOverlapedActors();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




};
