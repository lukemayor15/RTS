// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTS\Buildings\BaseResourceBuilding.h"
#include "GoldMine.generated.h"

/**
 *
 */
UCLASS()
class RTS_API AGoldMine : public ABaseResourceBuilding
{
	GENERATED_BODY()
	//Function to check what resource type it is overlapping
	virtual bool CheckResourceType(TArray<AActor*>  OtherActor) override;
	//Adds resouces
	virtual void AddResource() override;
	//How much resource it adds
	virtual void SetResourceIncreaseAmount() override;
	//The start values of the building
	virtual void SetStartValues() override;

};