// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitController.h"
#include "Unit.h"
#include "NavMesh/NavMeshBoundsVolume.h"


void AUnitController::BeginPlay()
{
	Super::BeginPlay();
}


void AUnitController::Tick(float DeltaTime)
{
	if (PawnAsUnit)
	{

		if (PawnAsUnit->IsMoving)
		{
			

			if (PawnAsUnit->MoveTarget != PawnAsUnit->GetActorLocation())
			{
				PawnAsUnit->MoveAnimation();
				MoveToLocation(PawnAsUnit->MoveTarget,0.0f, false, true, true, false);
				FVector HeightChanger = PawnAsUnit->GetActorLocation();
				HeightChanger.Z = 0;
				PawnAsUnit->SetActorLocation(HeightChanger);

				FVector DirectionToTarget = (PawnAsUnit->MoveTarget - PawnAsUnit->GetActorLocation());
				float SidewaysDotToTarget = FVector::DotProduct(DirectionToTarget, PawnAsUnit->GetActorRightVector());
				float DeltaYawDesired = FMath::Atan2(SidewaysDotToTarget, SidewaysDotToTarget);
				PawnAsUnit->AddRotationInput(DeltaYawDesired);
			}
			else
			{
				PawnAsUnit->IdleAnimation();
				PawnAsUnit->IsMoving = false;
				
			}

			
			
		}
	}
	
}

void AUnitController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PawnAsUnit = Cast<AUnit>(GetPawn());
}

void AUnitController::OnUnPossess()
{
	Super::OnUnPossess();
	PawnAsUnit = nullptr;
}