// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingButtonUserWidget.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class RTS_API UBuildingButtonUserWidget : public UUserWidget
{
    GENERATED_BODY()
private:

    virtual void NativeConstruct() override;

    virtual void Tick(float DeltaTime);


public:
    //pointer to uniform grid panel calss
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    class UUniformGridPanel* BuildingGrid1;

    //Creates buttons to be used for mouse/screen border movement
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UButton* BuildingButton;
    //pointer to button
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UButton* DefaultHudButton;
    //pointer to playerPawn
    UPROPERTY(BlueprintReadOnly)
    class APlayerPawn* PlayerAsPawn;
    //Checks if the player have enough resurces to build building or unit.
    UFUNCTION(Blueprintcallable)
    bool CheckCost(int WoodCost, int FoodCost, int StoneCost, int GoldCost);
    //used to generate buttons for the building grid
    UFUNCTION(Blueprintcallable)
    void CallGenerateButtons(TSubclassOf<class UUserWidget> Hud);
    //fucntion to set the get the player pawn
    UFUNCTION(Blueprintcallable)
    class APlayerPawn* GetPlayerPawn();

};
