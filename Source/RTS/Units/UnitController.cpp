// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitController.h"
#include "Unit.h"
#include "NavMesh/NavMeshBoundsVolume.h"


void AUnitController::BeginPlay()
{
	Super::BeginPlay();
}

//Tick Function
void AUnitController::Tick(float DeltaTime)
{
	//null pointer check
	if (PawnAsUnit)
	{
		//Check is pawn is Moving
		if (PawnAsUnit->IsMoving)
		{
			
			//Have we reach the move target
			if (PawnAsUnit->MoveTarget != PawnAsUnit->GetActorLocation())
			{
				//set the unit animation move
				PawnAsUnit->MoveAnimation();
				//Move unit to move target
				MoveToLocation(PawnAsUnit->MoveTarget,0.0f, false, true, true, false);
				//Keep the unit z position to 0
				FVector HeightChanger = PawnAsUnit->GetActorLocation();
				HeightChanger.Z = 0;
				PawnAsUnit->SetActorLocation(HeightChanger);

				//Get direction to target
				FVector DirectionToTarget = (PawnAsUnit->MoveTarget - PawnAsUnit->GetActorLocation());
				//sdie wats dot produicts
				float SidewaysDotToTarget = FVector::DotProduct(DirectionToTarget, PawnAsUnit->GetActorRightVector());
				//The yaw we desired
				float DeltaYawDesired = FMath::Atan2(SidewaysDotToTarget, SidewaysDotToTarget);
				//add the desired yaw to this unit
				PawnAsUnit->AddRotationInput(DeltaYawDesired);
			}
			//if we done move set is moving to false and set animation to idle
			else
			{
				PawnAsUnit->IdleAnimation();
				PawnAsUnit->IsMoving = false;
				
			}

			
			
		}
	}
	
}
//when possed set PawnAsUnit to the possed unit
void AUnitController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PawnAsUnit = Cast<AUnit>(GetPawn());
}
//when not possed set it to null
void AUnitController::OnUnPossess()
{
	Super::OnUnPossess();
	PawnAsUnit = nullptr;
}