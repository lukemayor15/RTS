// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseResourceBuilding.h"
#include "RTS\Player/PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "RTS\Hud/RTSHUD.h"
#include "RTS\Player/RTSPlayerController.h"
#include "RTS\UserWidgets/CameraControl.h"


void ABaseResourceBuilding::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GetOverlapedActors();
}

void ABaseResourceBuilding::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GetOverlapedActors();
}



void ABaseResourceBuilding::BeginPlay()
{
	Super::BeginPlay();
	PlayerAsPawn = static_cast<APlayerPawn*>(GetWorld()->GetFirstPlayerController()->GetPawn());
	IsPlaced = false;
	Selected = false;
	CanBePlaced = false;
	IncreaseDone = false;
	BoxCollision->GetGenerateOverlapEvents();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseBuilding::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ABaseBuilding::OnOverlapEnd);       // set up a notification for when this component overlaps something
	OnClicked.AddDynamic(this, &ABaseBuilding::OnSelected);

	BoxCollision->GetBodyInstance()->bUseCCD = true;
	IncreaseTime = 10.0f;
	SetResourceIncreaseAmount();
	GetOverlapedActors();
}

bool ABaseResourceBuilding::CheckResourceType(TArray<AActor*>  OtherActor)
{
	if (OtherActor.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can Build"));
		return true;
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cant"));
		return false;
	}
	
}


void ABaseResourceBuilding::OnSelected(AActor* Target, FKey ButtonPressed)
{

	if (IsPlaced && !Selected)
	{
		AddToList();
	}
	else if (CanBePlaced && IncreaseDone == false)
	{
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ABaseResourceBuilding::AddResource, IncreaseTime, true, 0.0f);
		
	}

}
void ABaseResourceBuilding::GetOverlapedActors()
{

	TArray<AActor*> OverlapedActors;
	GetOverlappingActors(OverlapedActors, TSubclassOf <AActor>());

	if (CheckResourceType(OverlapedActors))
	{
		CanBePlaced = true;

	}
	else
	{
		CanBePlaced = false;
	}
}

void ABaseResourceBuilding::AddResource()
{
	//Gets Overrided based on building type
}

void ABaseResourceBuilding::SetResourceIncreaseAmount()
{
	//Gets Overrided based on building type
}
