// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTS\Buildings\BaseResourceBuilding.h"
#include "House.generated.h"

/**
 *
 */
UCLASS()
class RTS_API AHouse : public ABaseResourceBuilding
{
	GENERATED_BODY()
	//Adds the resoruce to the player controller and update UI
	virtual void AddResource() override;
	//Set the resouce increase amount
	virtual void SetResourceIncreaseAmount() override;
	//set the initial start values of this buildings
	virtual void SetStartValues() override;


};
