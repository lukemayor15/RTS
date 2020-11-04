// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitController.h"
#include "Unit.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "Navigation/CrowdFollowingComponent.h"




AUnitController::AUnitController()
{
	CrowdComponent = CreateDefaultSubobject<UCrowdFollowingComponent>(TEXT("CrowdFollowingComponent"));

	CrowdComponent->SetCrowdSimulationState(ECrowdSimulationState::Enabled);
	CrowdComponent->SetCrowdAffectFallingVelocity(false);
	CrowdComponent->SetCrowdRotateToVelocity(true);
	CrowdComponent->SetCrowdAnticipateTurns(true);
	CrowdComponent->SetCrowdObstacleAvoidance(true);
	CrowdComponent->SetCrowdSeparation(true);
	CrowdComponent->SetCrowdOptimizeVisibility(true);
	CrowdComponent->SetCrowdOptimizeTopology(true);
	CrowdComponent->SetCrowdPathOffset(false);
	CrowdComponent->SetCrowdSlowdownAtGoal(true);

	CrowdComponent->SetCrowdSeparationWeight(200.0f);
	CrowdComponent->SetCrowdCollisionQueryRange(1000.0f);
	CrowdComponent->SetCrowdPathOptimizationRange(1000.0f);
	CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
	CrowdComponent->SetCrowdAvoidanceRangeMultiplier(1.0f);

	
}
void AUnitController::BeginPlay()
{
	Super::BeginPlay();
	MoveToStarted = false;
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
				if (MoveToStarted == false || PreMoveTarget != PawnAsUnit->MoveTarget)
				{
					CallMoveTo();
				}
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
				MoveToStarted = false;
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

void AUnitController::CallMoveTo()
{
	if (PawnAsUnit != nullptr)
	{
		MoveToLocation(PawnAsUnit->MoveTarget, 20.0f, false, true, true, false,0,false);
		MoveToStarted = true;
	}

	PreMoveTarget = PawnAsUnit->MoveTarget;

}