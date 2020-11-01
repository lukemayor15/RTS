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

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    class UUniformGridPanel* BuildingGrid1;

    //Creates buttons to be used for mouse/screen border movement
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UButton* BuildingButton;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UButton* DefaultHudButton;

    UPROPERTY(BlueprintReadOnly)
    class APlayerPawn* PlayerAsPawn;

    UFUNCTION(Blueprintcallable)
    bool CheckCost(int WoodCost, int FoodCost, int StoneCost, int GoldCost);

    UFUNCTION(Blueprintcallable)
    void CallGenerateButtons(TSubclassOf<class UUserWidget> Hud);

    UFUNCTION(Blueprintcallable)
    class APlayerPawn* GetPlayerPawn();

};
