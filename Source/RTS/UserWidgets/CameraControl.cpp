// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraControl.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Components/GridPanel.h"
#include "Components/ProgressBar.h"
#include "UObject/ConstructorHelpers.h"
#include "RTS\Player\PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "RTS\Buildings\BaseBuilding.h"
#include "BuildingButtonUserWidget.h"
#include "RTS\Player\RTSPlayerController.h"
#include "Components/TextBlock.h"

UCameraControl::UCameraControl(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
    static ConstructorHelpers::FClassFinder<UUserWidget> BuildingHud(TEXT("/Game/UserWidgets/BuildingHud/StandardBuildingHud"));
    HUDWidgetClass = BuildingHud.Class;


}

void UCameraControl::NativeConstruct()
{
    Super::NativeConstruct();

    PlayerAsPawn = static_cast<APlayerPawn*>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (PlayerAsPawn != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("not null"));
    }

    Top->OnHovered.AddDynamic(this, &UCameraControl::MoveUp);
    Down->OnHovered.AddDynamic(this, &UCameraControl::MoveDown);
    Left->OnHovered.AddDynamic(this, &UCameraControl::MoveLeft);
    Right->OnHovered.AddDynamic(this, &UCameraControl::MoveRight);

    TopRight->OnHovered.AddDynamic(this, &UCameraControl::MoveTopRight);
    BottomRight->OnHovered.AddDynamic(this, &UCameraControl::MoveBottomRight);
    TopLeft->OnHovered.AddDynamic(this, &UCameraControl::MoveTopLeft);
    BottomLeft->OnHovered.AddDynamic(this, &UCameraControl::MoveBottomLeft);



    Top->OnUnhovered.AddDynamic(this, &UCameraControl::StopMove);
    Down->OnUnhovered.AddDynamic(this, &UCameraControl::StopMove);
    Left->OnUnhovered.AddDynamic(this, &UCameraControl::StopMove);
    Right->OnUnhovered.AddDynamic(this, &UCameraControl::StopMove);
    TopRight->OnUnhovered.AddDynamic(this, &UCameraControl::StopMove);
    BottomRight->OnUnhovered.AddDynamic(this, &UCameraControl::StopMove);
    TopLeft->OnUnhovered.AddDynamic(this, &UCameraControl::StopMove);
    BottomLeft->OnUnhovered.AddDynamic(this, &UCameraControl::StopMove);



}

void UCameraControl::Tick(float DeltaTime)
{

}

//- movees the player pawn based on the hoverd button

void UCameraControl::MoveUp()
{
    PlayerAsPawn->SetButtonHoveredX(1.0f);
}
void UCameraControl::MoveDown()
{
    PlayerAsPawn->SetButtonHoveredX(-1.0f);
}

void UCameraControl::MoveLeft()
{
    PlayerAsPawn->SetButtonHoveredY(1.0f);
}
void UCameraControl::MoveRight()
{
    PlayerAsPawn->SetButtonHoveredY(-1.0f);
}
void UCameraControl::MoveTopRight()
{
    PlayerAsPawn->SetButtonHoveredX(0.7f);
    PlayerAsPawn->SetButtonHoveredY(-0.7f);
}

void UCameraControl::MoveBottomRight()
{
    PlayerAsPawn->SetButtonHoveredX(-0.7f);
    PlayerAsPawn->SetButtonHoveredY(-0.7f);
}

void UCameraControl::MoveTopLeft()
{
    PlayerAsPawn->SetButtonHoveredX(0.7f);
    PlayerAsPawn->SetButtonHoveredY(0.7f);
}

void UCameraControl::MoveBottomLeft()
{
    PlayerAsPawn->SetButtonHoveredX(-0.7f);
    PlayerAsPawn->SetButtonHoveredY(0.7f);
}
//When no moveement button is being hoverd
void UCameraControl::StopMove()
{
    //Stop the player pawn movement
    PlayerAsPawn->StopButtonHovered(0);
}
//end of buttons hoverd section
//based on the widgetclass passed add it to the view port
void UCameraControl::GenereateButtons(TSubclassOf<class UUserWidget> NewWidgetClass)
{
    //null pointer check
    if (NewWidgetClass != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT(" Button generates"));

        //set the newGrid select pointer to point to the new created widget of hte widgetcalss that is passed to this function.
        UBuildingButtonUserWidget* NewGridSelect = CreateWidget<UBuildingButtonUserWidget>(GetWorld(), NewWidgetClass);
        // check if we are buildGrid1 has a child that is the same as NewGridSelect
        if (NewGridSelect != BuildingGrid1->GetChildAt(0))
        {
            //child null pointer check
            if (BuildingGrid1->GetChildAt(0) != nullptr)
            {
                //remove the BuildingGrid1 child from it parent
                BuildingGrid1->GetChildAt(0)->RemoveFromParent();
            }
            //and the newGridSelect as the new child
            BuildingGrid1->AddChildToUniformGrid(NewGridSelect->BuildingGrid1);
        }

    }
}
//When a unit or building is selected this is called to update the HUD 
void UCameraControl::UpdateSelectGrid()
{
    //if not empty
    if (PlayerAsPawn->CurrentController->BuildingList.Num() >= 0)
    {
        //Update the health bar and the the BuildingName Text
        HealthBar->SetPercent((PlayerAsPawn->CurrentController->BuildingList[0]->MaxHealth / PlayerAsPawn->CurrentController->BuildingList[0]->Health) * 100);
        UE_LOG(LogTemp, Warning, TEXT(" Calulated "));
        SelectedName->SetText(FText::FromString(PlayerAsPawn->CurrentController->BuildingList[0]->BuildingName));
    }
    //Yet to be implemneted but works the same way as the buildingList one
    else if (PlayerAsPawn->CurrentController->UnitList.Num() >= 0)
    {

    }

}
//Update the resources Hud when a resouce value is changed
void UCameraControl::UpdateResoruceAmount()
{
    StoneTextCurrent->SetText(FText::FromString(FString::FromInt(PlayerAsPawn->CurrentController->Stone)));
    WoodTextCurrent->SetText(FText::FromString(FString::FromInt(PlayerAsPawn->CurrentController->Wood)));
    PopTextCurrent->SetText(FText::FromString(FString::FromInt(PlayerAsPawn->CurrentController->Food)));
    PopTextMax->SetText(FText::FromString(FString::FromInt(PlayerAsPawn->CurrentController->MaxFood)));
    GoldTextCurrent->SetText(FText::FromString(FString::FromInt(PlayerAsPawn->CurrentController->Gold)));
}




