// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuilding.h"
#include "BaseResourceBuilding.generated.h"

/**
 *
 */
UCLASS()
class RTS_API ABaseResourceBuilding : public ABaseBuilding
{
	GENERATED_BODY()

public:


	int32 ResourceIncreaseAmount;

	float IncreaseTime;

	uint32 IncreaseDone : 1;


	/** called when something enters the boxomponent */

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	/** called when something leaves the boxomponent component */

	virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual bool CheckResourceType(TArray<AActor*> OtherActor);

	 void GetOverlapedActors() override;

	virtual void AddResource();

	virtual void SetResourceIncreaseAmount();

	virtual void OnSelected(AActor* Target, FKey ButtonPressed) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
