// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerController.h"
#include "PlayerPawn.h"
#include "RTS\Units\Unit.h"
#include "RTS\Buildings\BaseBuilding.h"



ARTSPlayerController::ARTSPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

}


