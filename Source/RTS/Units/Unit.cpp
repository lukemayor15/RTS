// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit.h"
#include "Components/StaticMeshComponent.h"
#include "RTS\Player\PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"
#include "UnitController.h"



// Sets default values
AUnit::AUnit()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMesh->AttachTo(RootComponent);
	MovementSpeed = 270.0f;

}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	CurrentController = static_cast<AUnitController*>(GetController());
	YawSpeed = 270.0f;
}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ConsumeMovementInputVector();
	ConsumeRotationInput(DeltaTime);
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

//implmented in blueprints for animation
void AUnit::IdleAnimation_Implementation()
{

}
//implmented in blueprints for animation

void AUnit::MoveAnimation_Implementation()
{

}




