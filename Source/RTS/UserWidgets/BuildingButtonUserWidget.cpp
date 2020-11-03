// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingButtonUserWidget.h"
#include "Components/Button.h"
#include "UObject/ConstructorHelpers.h"
#include "RTS\Player\PlayerPawn.h"
#include "RTS\Player\RTSPlayerController.h"
#include "CameraControl.h"
#include "RTS\Hud\RTSHUD.h"


void UBuildingButtonUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

    //set playeraspawn to the current player pawn
    PlayerAsPawn = static_cast<APlayerPawn*>(GetWorld()->GetFirstPlayerController()->GetPawn());
    //null pointer check for debug
    if (PlayerAsPawn != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("not null"));
    }
}

void UBuildingButtonUserWidget::Tick(float DeltaTime)
{

}
//Used to check the if th eplayer have enough resoruces for building/unit
bool UBuildingButtonUserWidget::CheckCost(int WoodCost, int FoodCost, int StoneCost, int GoldCost)
{
    //null pointer check
    if (PlayerAsPawn == nullptr)
    {
        //if null set playeraspawn to the player pawn
        PlayerAsPawn = static_cast<APlayerPawn*>(GetWorld()->GetFirstPlayerController()->GetPawn());
    }
    //Check if we have enough resoruces if so return true
    if (PlayerAsPawn->CurrentController->Wood >= WoodCost && (PlayerAsPawn->CurrentController->Food + FoodCost) <= PlayerAsPawn->CurrentController->MaxFood && PlayerAsPawn->CurrentController->Stone >= StoneCost && PlayerAsPawn->CurrentController->Gold >= GoldCost)
    {
        return true;
    }
    return false;
}
//Genreate buttons for the building grid
void UBuildingButtonUserWidget::CallGenerateButtons(TSubclassOf<class UUserWidget> Hud)
{
    //null pointer check
    if (PlayerAsPawn == nullptr)
    {
        //if null set playeraspawn to the player pawn
        PlayerAsPawn = static_cast<APlayerPawn*>(GetWorld()->GetFirstPlayerController()->GetPawn());
        //called generate buttons
        PlayerAsPawn->HudForSelectionBox->CurrentWidget->GenereateButtons(Hud);
    }
    else
    {
        //called generate buttons
        PlayerAsPawn->HudForSelectionBox->CurrentWidget->GenereateButtons(Hud);
    }
}
//get the player pawn 
APlayerPawn* UBuildingButtonUserWidget::GetPlayerPawn()
{
    //check for null pointer
    if (PlayerAsPawn == nullptr)
    {
        //if null set playeraspawn to the player  pawn

        PlayerAsPawn = static_cast<APlayerPawn*>(GetWorld()->GetFirstPlayerController()->GetPawn());
        
    }

    //return playeraspawn
    return PlayerAsPawn;
}
