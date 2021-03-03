// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitController.h"
#include "Unit.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "RTS\Units\Enemys\BaseEnemy.h"



AUnitController::AUnitController()
{
	//intialse values for the UCrowdFollowingComponent
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
	//Set the timer time
	TimerTime = 0.33f;
	// start a timer for the unit AI update instead of using event tick
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AUnitController::AITimer, TimerTime, true, 0.0f);
	MoveToStarted = false;
	
}

//Tick Function
void AUnitController::Tick(float DeltaTime)
{
	if (PawnAsUnit)
	{
		//Check is pawn is Moving, 
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


			if (PawnAsUnit->IsAttacking == true && PawnAsUnit->MoveTarget != PawnAsUnit->TargetedEnemy->GetActorLocation())
			{

				PawnAsUnit->CheckMovementPositionChangeAttack();
			}
			
			//change from magic numbers, and split up into attacking move and not attacking move
			if (vectorLength > 40.0f && PawnAsUnit->IsAttacking == false || vectorLength > 140.0f && PawnAsUnit->IsAttacking == true)
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
				//Check if the unit is attacking and if the targetenemy is not null
				if (PawnAsUnit->IsAttacking && PawnAsUnit->TargetedEnemy != nullptr && AttackStarted == false)
				{
					//set attack started to true
					AttackStarted = true;
					//create a timer that runs the same time as it animation, to attack the selected targeted
					GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AUnitController::Attack, 2.33f, true, 0.0f);
				}
				else if(PawnAsUnit->IsAttacking == false)
				{
					//set the unit animation to idle
					//set the unit ISmoving to false and the controller moveToStarted to false
					PawnAsUnit->IdleAnimation();
					PawnAsUnit->IsMoving = false;
					MoveToStarted = false;
					
				}

				// add in attack function to attack the enemy one the destination is reached, 		
			}
			PawnAsUnit->CheckOverlap();
		}
		
	}
}

//Attack function
void AUnitController::Attack()
{
	//check for nullptr
	if (PawnAsUnit != nullptr)
	{
		//check for nullptr
		if (PawnAsUnit->TargetedEnemy != nullptr)
		{
			//set the attack animation and called take damage fuincion from the enemy.
			PawnAsUnit->AttackAnimation();
			PawnAsUnit->TargetedEnemy->TakeDamage(10);
		}
		//if targeted enemy is null, it means it is destroyed
		//reset the values of the unit to be idle
		else
		{
			StopAttack();

		}
	}
}

void AUnitController::StopAttack()
{
	PawnAsUnit->IsAttacking = false;
	PawnAsUnit->IdleAnimation();
	GetWorldTimerManager().ClearTimer(AttackTimerHandle);
	AttackStarted = false;
	PawnAsUnit->CheckOverlap();
}

void AUnitController::CallMoveTo()
{
	if (PawnAsUnit != nullptr)
	{
		if (PawnAsUnit->IsAttacking == true)
		{
			MoveToLocation(PawnAsUnit->MoveTarget, 40.0f, false, true, true, false, 0, false);
			//we have started to Move
			MoveToStarted = true;
		}
		else
		{
			//Move to movetarget
			MoveToLocation(PawnAsUnit->MoveTarget, 40.0f, false, true, true, false, 0, false);
			//we have started to Move
			MoveToStarted = true;
		}
		
	}
	//set the PreMoveTarget to new MoveTarget
	PreMoveTarget = PawnAsUnit->MoveTarget;

}