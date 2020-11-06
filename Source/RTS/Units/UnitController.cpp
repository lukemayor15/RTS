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

	CrowdComponent->SetCrowdSeparationWeight(100.0f);
	CrowdComponent->SetCrowdCollisionQueryRange(1000.0f);
	CrowdComponent->SetCrowdPathOptimizationRange(1000.0f);
	CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
	CrowdComponent->SetCrowdAvoidanceRangeMultiplier(1.0f);

}
void AUnitController::BeginPlay()
{
	Super::BeginPlay();
	TimerTime = 0.33f;

	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AUnitController::AITimer, TimerTime, true, 0.0f);
	MoveToStarted = false;
	
}

//Tick Function
void AUnitController::Tick(float DeltaTime)
{
	if (PawnAsUnit)
	{
		//Check is pawn is Moving
		if (PawnAsUnit->IsMoving)
		{
			//Get direction to target
			FVector DirectionToTarget = (PawnAsUnit->MoveTarget - PawnAsUnit->GetActorLocation());
			//sdie wats dot produicts
			float SidewaysDotToTarget = FVector::DotProduct(DirectionToTarget, PawnAsUnit->GetActorRightVector());
			//The yaw we desired
			float DeltaYawDesired = FMath::Atan2(SidewaysDotToTarget, SidewaysDotToTarget);
			//add the desired yaw to this unit
			PawnAsUnit->AddRotationInput(DeltaYawDesired);
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

//AI timer, this is used to update what the AI is doing
void AUnitController::AITimer()
{
	//null pointer check
	if (PawnAsUnit)
	{
		//Check is pawn is Moving
		if (PawnAsUnit->IsMoving)
		{
			//Have we reach the move target
			FVector ActorLoc = PawnAsUnit->GetActorLocation();
			ActorLoc.Z = 0.0f;

			//Get the diffrence between the two vectors
			//first minus the two, then called the size functino witch returns the length of the vector
			FVector InRangeCheck = PawnAsUnit->MoveTarget - ActorLoc;
			int vectorLength = InRangeCheck.Size();
			if (vectorLength > 20.0f && vectorLength > 20.0f)
			{
				//set the unit animation move
				PawnAsUnit->MoveAnimation();
				//Move unit to move target
				if (MoveToStarted == false || PreMoveTarget != PawnAsUnit->MoveTarget)
				{
					CallMoveTo();
				};
			}
			//If we done moving 
			else
			{
				//set the unit animation to idle
				//set the unit ISmoving to false and the controller moveToStarted to false
				PawnAsUnit->IdleAnimation();
				PawnAsUnit->IsMoving = false;
				MoveToStarted = false;
			}
		}
	}
}

void AUnitController::CallMoveTo()
{
	if (PawnAsUnit != nullptr)
	{
		//Move to movetarget
		MoveToLocation(PawnAsUnit->MoveTarget, 20.0f, false, true, true, false,0,false);
		//we have started to Move
		MoveToStarted = true;
	}
	//set the PreMoveTarget to new MoveTarget
	PreMoveTarget = PawnAsUnit->MoveTarget;

}