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

	virtual void CallMoveTo();

	UPROPERTY(EditAnywhere)
	uint32 MoveToStarted : 1;

	UPROPERTY(EditAnywhere)
	class UCrowdFollowingComponent* CrowdComponent;

	UPROPERTY(EditAnywhere)
	FVector PreMoveTarget;

protected:
	//poitner to Unit class
	UPROPERTY(BlueprintReadOnly, Category = "Unit")
		class 	AUnit* PawnAsUnit;
};
