// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTS\Buildings\BaseRecruitmentBuilding.h"
#include "Barracks.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API ABarracks : public ABaseRecruitmentBuilding
{
	GENERATED_BODY()
	
	ABarracks();
	virtual void SetStartValues() override;


};

