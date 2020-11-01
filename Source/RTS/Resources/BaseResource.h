// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseResource.generated.h"

UCLASS()
class RTS_API ABaseResource : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseResource();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
		class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		class UStaticMeshComponent* StaticMesh;


};
