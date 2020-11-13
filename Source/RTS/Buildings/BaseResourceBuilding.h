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

	//resource increase amount
	int32 ResourceIncreaseAmount;
	//increase rate time
	float IncreaseTime;

	//Check if the increase is done, be it setting the timer or on a one of increase
	uint32 IncreaseDone : 1;




	//used to check if the overlapping acctor is the correct resouce type
	virtual bool CheckResourceType(TArray<AActor*> OtherActor);

	void GetOverlapedActors() override;

	//Update player controler resource amount and updating the UI
	virtual void AddResource();

	//sets the reosurce increase amount
	virtual void SetResourceIncreaseAmount();

	//OnSelected function(When clicked on)
	virtual void OnSelected(AActor* Target, FKey ButtonPressed) override;

	virtual void Placing() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
