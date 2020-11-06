// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnitController.generated.h"

/**
 *
 */
UCLASS()
class RTS_API AUnitController : public AAIController
{
	GENERATED_BODY()

	AUnitController();

	virtual void Tick(float DeltaTime) override;


	virtual void BeginPlay() override;
	//called when the unitcontroller is posssesd
	virtual void OnPossess(class APawn* InPawn) override;
	//called when the unitcontroller UnPossess a unit
	virtual void OnUnPossess() override;

	//Replacing the tick function to imporve performance
	virtual void AITimer();
	//how often the AITimer function is called.
	float TimerTime;

	//offset value allowed betwen unit and targeted posistion
	float UnitOffset;

	//Set the actor to move to move target
	virtual void CallMoveTo();

	//Bool to check if unit is moving
	UPROPERTY(EditAnywhere)
	uint32 MoveToStarted : 1;

	//
	UPROPERTY(EditAnywhere)
	class UCrowdFollowingComponent* CrowdComponent;

	//Previous target to check if the move target has been updated
	UPROPERTY(EditAnywhere)
	FVector PreMoveTarget;

	/* Handle to manage the timer */
	FTimerHandle MemberTimerHandle;

protected:
	//poitner to Unit class
	UPROPERTY(BlueprintReadOnly, Category = "Unit")
		class 	AUnit* PawnAsUnit;
};
