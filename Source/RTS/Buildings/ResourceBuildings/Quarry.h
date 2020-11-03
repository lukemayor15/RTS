// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTS\Buildings\BaseResourceBuilding.h"
#include "Quarry.generated.h"

/**
 *
 */
UCLASS()
class RTS_API AQuarry : public ABaseResourceBuilding
{
	GENERATED_BODY()
	//Function to check the overlapping actor is of the correct resource type
	virtual bool CheckResourceType(TArray<AActor*>  OtherActor) override;
	//adds resource
	virtual void AddResource() override;
	//Sets the resource increase amount
	virtual void SetResourceIncreaseAmount() override;
	//set the start values
	virtual void SetStartValues() override;
};
