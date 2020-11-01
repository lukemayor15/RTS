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


	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(BlueprintReadOnly)
		uint32 Selected : 1;

	UPROPERTY(BlueprintReadOnly)
		uint32 IsMoving : 1;

	UPROPERTY(BlueprintReadOnly)
		FVector MoveTarget;

	UPROPERTY(BlueprintReadWrite)
		float YawInput;

	UPROPERTY(BlueprintReadOnly)
		class AUnitController* CurrentController;


	//add rotation input
	UFUNCTION(BlueprintCallable, Category = "Pawm|Input", meta = (Keywords = "ConsumeInput"))
		virtual float GetRotationInput();
	//clear rotatino or would update
	UFUNCTION(BlueprintCallable, Category = "Pawm|Input", meta = (Keywords = "ConsumeInput"))
		virtual float ConsumeRotationInput(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Pawm|Input", meta = (Keywords = "AddInput"))
		virtual void AddRotationInput(float DeltaYawDegrees);

	UFUNCTION(BlueprintNativeEvent)
	void IdleAnimation();

	UFUNCTION(BlueprintNativeEvent)
	void MoveAnimation();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zombie", meta = (CampMin = "0.0"))
		float YawSpeed;

	UPROPERTY(BlueprintReadWrite)
		float MovementSpeed;
};

