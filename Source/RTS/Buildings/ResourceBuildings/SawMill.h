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

	virtual bool CheckResourceType(TArray<AActor*>  OtherActor) override;
	virtual void AddResource() override;
	virtual void SetResourceIncreaseAmount() override;
	virtual void SetStartValues() override;
};
