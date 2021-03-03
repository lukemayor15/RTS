// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit.h"
#include "Components/StaticMeshComponent.h"
#include "RTS\Player\PlayerPawn.h"
#include "RTS\Player\RTSPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"
#include "UnitController.h"
#include "Components/SphereComponent.h"
#include "Enemys/BaseEnemy.h"
#include "RTS\Function Library\FunctionLibrary.h"
#include "DrawDebugHelpers.h"





// Sets default values
AUnit::AUnit()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	MovementSpeed = 270.0f;
	
}

// Called when the game starts or when spawned and set intial values
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	CurrentController = static_cast<AUnitController*>(GetController());
	PlayerAsPawn = static_cast<APlayerPawn*>(GetWorld()->GetFirstPlayerController()->GetPawn());
	YawSpeed = 270.0f;
	IsAttacking = false;
	IsMoving = false;
}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ConsumeMovementInputVector();
	ConsumeRotationInput(DeltaTime);
	if (!IsAttacking)
	{
		AttackRadiusCheck();
	}

}

// Called to bind functionality to input
void AUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


float AUnit::GetRotationInput()
{
	return YawInput;
}
//calulates the rotation impact,(rotated i the move direction)
float AUnit::ConsumeRotationInput(float DeltaTime)
{
	float RetVal = YawInput;
	float MaxYawThisFrame = YawSpeed * DeltaTime;
	FRotator DesiedRot = GetActorRotation() + FRotator(0.0f, FMath::Clamp(GetRotationInput(), -MaxYawThisFrame, MaxYawThisFrame), 0.0f);
	SetActorRotation(DesiedRot.Quaternion());
	YawInput = 0.0f;
	return RetVal;
}
//the rortation input
void AUnit::AddRotationInput(float DeltaYawDegrees)
{
	YawInput += DeltaYawDegrees;
}

void AUnit::CallStopAttack()
{
	CurrentController->StopAttack();
}

void AUnit::AttackRadiusCheck()
{
	TArray <FHitResult> RV_Hit;
	FCollisionShape Shape;
	Shape.SetSphere(800.0f);
	FVector ActorLocation = GetActorLocation();

	//DrawDebugSphere(GetWorld(), ActorLocation, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
	//check if there is a pawn actors in this radius, 
	if (GetWorld()->SweepMultiByChannel(RV_Hit, ActorLocation, FVector(ActorLocation.X, ActorLocation.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape))
	{
		//debug text 
		UE_LOG(LogTemp, Warning, TEXT("Collision"));
		//loop through all actors for the sweep 
		for (int i = 0; i < RV_Hit.Num() ; i++)
		{
			//check if there are  a ABaseEnemy Class
			if (RV_Hit[i].Actor->IsA(ABaseEnemy::StaticClass()))
			{
				//if the current unit is not moving or alreadt attacking
				if (IsMoving != true && IsAttacking != true)
				{
					//create an array called movement points
					TArray<FVector> CheckedMovementPoints;
					// called group movement2 to check if any possible move ponits to the target
					CheckedMovementPoints =UFunctionLibrary::GroupMovement2(RV_Hit[i], PlayerAsPawn->CurrentController, 100.0f, 40.0f, RV_Hit[i].Actor->GetActorLocation(), true, GetWorld(), true);
					//is CheckedMovementPoints empty
					if (CheckedMovementPoints.Num() != 0)
					{
						//set the units move target
						MoveTarget = CheckedMovementPoints[0];
						// set IS moving and attacking is true
						IsMoving = true;
						IsAttacking = true;
						//make the enemy that it is moving too its targeted enemy.
						TargetedEnemy = Cast<ABaseEnemy>(RV_Hit[i].Actor);
					}
					
				}
			}
		}
	}
}
void AUnit::CheckMovementPositionChangeAttack()
{
	//create an array called movement points
	TArray<FVector> CheckedMovementPoints;
	// called group movement2 to check if any possible move ponits to the target
	CheckedMovementPoints = UFunctionLibrary::CheckSingleTarget(PlayerAsPawn->CurrentController, 100.0f, 40.0f, TargetedEnemy->GetActorLocation(), true, GetWorld(), true);

	if (CheckedMovementPoints.Num() != 0)
	{
		//set the units move target
		MoveTarget = CheckedMovementPoints[0];
		// set IS moving and attacking is true
	}
	
}

void AUnit::CheckMovementPositionChange()
{
	//create an array called movement points
	TArray<FVector> CheckedMovementPoints;
	// called group movement2 to check if any possible move ponits to the target
	CheckedMovementPoints = UFunctionLibrary::CheckSingleTarget(PlayerAsPawn->CurrentController, 100.0f, 40.0f, MoveTarget, false, GetWorld(), true);

	if (CheckedMovementPoints.Num() != 0)
	{
		//set the units move target
		MoveTarget = CheckedMovementPoints[0];
		// set IS moving and attacking is true
	}

}
void AUnit::CheckOverlap()
{//if have subclass change to tsubclass of
	TArray<AActor*> OverlapedActors;
	GetOverlappingActors(OverlapedActors, ABaseEnemy::StaticClass());
	if (OverlapedActors.Num() != 0 && IsMoving != true && IsAttacking != true )
	{

		MoveTarget = OverlapedActors[0]->GetActorLocation();
		MoveTarget.X += 100.0f;
		IsMoving = true;
		IsAttacking = true;
		TargetedEnemy = Cast<ABaseEnemy>(OverlapedActors[0]);
	}
}

//implmented in blueprints for animation
void AUnit::IdleAnimation_Implementation()
{

}
//implmented in blueprints for animation

void AUnit::MoveAnimation_Implementation()
{

}
//implmented in blueprints for animation
void AUnit::AttackAnimation_Implementation()
{

}





