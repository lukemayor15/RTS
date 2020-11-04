// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Unit.generated.h"

UCLASS()
class RTS_API AUnit : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//pointer to staticmeshcomponet
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;


	//selected bool
	UPROPERTY(BlueprintReadOnly)
	uint32 Selected : 1;
	//isMOving Bool
	UPROPERTY(BlueprintReadOnly)
	uint32 IsMoving : 1;
	//Move target Fvector
	UPROPERTY(BlueprintReadOnly)
	FVector MoveTarget;
	//Yawinput
	UPROPERTY(BlueprintReadWrite)
	float YawInput;
	//pointer to UnitController
	UPROPERTY(BlueprintReadOnly)
	class AUnitController* CurrentController;


	//Get rotation input
	UFUNCTION(BlueprintCallable, Category = "Pawm|Input", meta = (Keywords = "ConsumeInput"))
		virtual float GetRotationInput();
	//clear rotatino or would update
	UFUNCTION(BlueprintCallable, Category = "Pawm|Input", meta = (Keywords = "ConsumeInput"))
		virtual float ConsumeRotationInput(float DeltaTime);
	//add rotation input
	UFUNCTION(BlueprintCallable, Category = "Pawm|Input", meta = (Keywords = "AddInput"))
		virtual void AddRotationInput(float DeltaYawDegrees);

	
	//Bluepprint implemented  function for idel animation
	UFUNCTION(BlueprintNativeEvent)
	void IdleAnimation();
	//Bluepprint implemented  function for move animation
	UFUNCTION(BlueprintNativeEvent)
	void MoveAnimation();
protected:
	//Yaw speed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit", meta = (CampMin = "0.0"))
		float YawSpeed;
	//MovementSpeed
	UPROPERTY(BlueprintReadWrite)
		float MovementSpeed;
};

