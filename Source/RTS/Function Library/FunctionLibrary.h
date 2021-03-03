// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API UFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:
	static TArray<FVector> GroupMovement2(FHitResult RV_Hit, class ARTSPlayerController* CurrentController, float RadiusChangeAmount, float SphereRadius, FVector Position, bool Attacking, UWorld* World, bool single);
	static TArray<FVector> CheckSingleTarget(ARTSPlayerController* CurrentController, float RadiusChangeAmount, float SphereRadius, FVector Position, bool Attacking, UWorld* World, bool single);
};
