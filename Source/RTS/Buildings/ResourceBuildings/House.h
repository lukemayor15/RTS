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
	virtual void AddResource() override;
	virtual void SetResourceIncreaseAmount() override;
	virtual void SetStartValues() override;


};
