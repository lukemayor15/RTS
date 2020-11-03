// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTS\Buildings\BaseResourceBuilding.h"
#include "SawMill.generated.h"

/**
 *
 */
UCLASS()
class RTS_API ASawMill : public ABaseResourceBuilding
{
	GENERATED_BODY()
public:
	//Check if the overlapping actor is the correct resource type
	virtual bool CheckResourceType(TArray<AActor*>  OtherActor) override;
	//adds resoruce to player controller and updates UI
	virtual void AddResource() override;
	//Set the resouce increase amount used in add resource
	virtual void SetResourceIncreaseAmount() override;
	//set the inital start values of this building type
	virtual void SetStartValues() override;
};
