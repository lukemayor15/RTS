// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CameraControl.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class RTS_API UCameraControl : public UUserWidget
{
    GENERATED_BODY()
public:

    UCameraControl(const FObjectInitializer& ObjectInitializer);

    virtual void NativeConstruct() override;

    virtual void Tick(float DeltaTime);

    //Creates buttons to be used for mouse/screen border movement
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        class UButton* Left;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        class UButton* Down;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        class UButton* Top;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        class UButton* Right;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        class UButton* TopRight;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        class UButton* BottomRight;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        class UButton* TopLeft;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        class UButton* BottomLeft;

    //end

    // For building
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        class UButton* BuildingTest;
    //testing purpuse

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UUniformGridPanel* BuildingGrid1;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UGridPanel* SelectGrid;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UProgressBar* HealthBar;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTextBlock* SelectedName;

    //Text boxes for resources
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTextBlock* StoneTextCurrent;
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTextBlock* PopTextCurrent;
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTextBlock* PopTextMax;
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTextBlock* WoodTextCurrent;
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UTextBlock* GoldTextCurrent;
    // end of resources text boxes
    UPROPERTY(BlueprintReadOnly)
        class APlayerPawn* PlayerAsPawn;


    UPROPERTY(EditAnywhere, Category = Players, meta = (AllowPrivateAccess = "true"))
        TSubclassOf<class ABaseBuilding> BaseBuilding;


    //Which way to move based op
    UPROPERTY(BlueprintReadOnly)
        float AxisVal;
    //Functions to tell pawn to move correct direction
    UFUNCTION()
        void MoveUp();
    UFUNCTION()
        void MoveDown();
    UFUNCTION()
        void MoveLeft();
    UFUNCTION()
        void MoveRight();
    UFUNCTION()
        void MoveTopRight();
    UFUNCTION()
        void MoveBottomRight();
    UFUNCTION()
        void MoveTopLeft();
    UFUNCTION()
        void MoveBottomLeft();


    //crete buttons base on selected Widget cvlass
    UFUNCTION()
        void GenereateButtons(TSubclassOf<class UUserWidget> NewWidgetClass);


    //Update the health and text for the selected unit or building
    UFUNCTION()
        void UpdateSelectGrid();

    UFUNCTION()
        void UpdateResoruceAmount();
    //called when not over a button to stop movement
    UFUNCTION()
        void StopMove();

private:

    //sub clas of userwidget
    UPROPERTY(EditAnywhere, Category = "Hud")
        TSubclassOf<class UUserWidget> HUDWidgetClass;


};
