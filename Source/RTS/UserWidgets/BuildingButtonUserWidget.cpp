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

    PlayerAsPawn = static_cast<APlayerPawn*>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (PlayerAsPawn != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("not null"));
    }
}

void UBuildingButtonUserWidget::Tick(float DeltaTime)
{

}

bool UBuildingButtonUserWidget::CheckCost(int WoodCost, int FoodCost, int StoneCost, int GoldCost)
{
    if (PlayerAsPawn == nullptr)
    {
        PlayerAsPawn = static_cast<APlayerPawn*>(GetWorld()->GetFirstPlayerController()->GetPawn());
    }
    if (PlayerAsPawn->CurrentController->Wood >= WoodCost && (PlayerAsPawn->CurrentController->Food + FoodCost) <= PlayerAsPawn->CurrentController->MaxFood && PlayerAsPawn->CurrentController->Stone >= StoneCost && PlayerAsPawn->CurrentController->Gold >= GoldCost)
    {
        
        return true;
    }
    return false;
}

void UBuildingButtonUserWidget::CallGenerateButtons(TSubclassOf<class UUserWidget> Hud)
{
    if (PlayerAsPawn == nullptr)
    {
        PlayerAsPawn = static_cast<APlayerPawn*>(GetWorld()->GetFirstPlayerController()->GetPawn());
        PlayerAsPawn->HudForSelectionBox->CurrentWidget->GenereateButtons(Hud);
    }
    else
    {
        PlayerAsPawn->HudForSelectionBox->CurrentWidget->GenereateButtons(Hud);
    }
}

APlayerPawn* UBuildingButtonUserWidget::GetPlayerPawn()
{
    if (PlayerAsPawn == nullptr)
    {
        PlayerAsPawn = static_cast<APlayerPawn*>(GetWorld()->GetFirstPlayerController()->GetPawn());
        
    }

    return PlayerAsPawn;
}
