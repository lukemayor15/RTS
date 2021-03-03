// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary.h"
#include "DrawDebugHelpers.h"
#include "RTS\Player\RTSPlayerController.h"


//make make in own function that takes permaters so isntead of two fundtions that simlair just one
TArray<FVector> UFunctionLibrary::GroupMovement2(FHitResult RV_Hit, ARTSPlayerController* CurrentController, float RadiusChangeAmount, float SphereRadius, FVector Position, bool Attacking, UWorld* World, bool single)
{
	// do we need to increase the radius check
	bool IncreaseRaduius = false;
	//int to count how many radius checks have been made, after 8 it increase the radius
	int RadiusCheck = 0;


	//FVector Tarray , use to store location of the move points
	TArray<FVector> MovementPoints;
	//get the mouse position
	FVector OriginalMovePoint = Position;
	//set z to 0 as we can ingore that value
	OriginalMovePoint.Z = 0.0f;
	//Second mouse position set it to the , mouse position
	FVector MovePoint = OriginalMovePoint;
	//Re-initialize hit info
	RV_Hit.Init();
	//Coolision shape info
	FCollisionShape Shape;
	Shape.SetSphere(SphereRadius);
	//float for raduous change amount
	

	//Draw a debug sphere
	DrawDebugSphere(World->GetWorld(), OriginalMovePoint, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
	//cCreate a sweep single by chaneel to check if the mouse position is empty, no overlapping actors
	if (!World->GetWorld()->SweepSingleByChannel(RV_Hit, OriginalMovePoint, FVector(OriginalMovePoint.X, OriginalMovePoint.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape) || Attacking == true)
	{
		//if no actors are hit we can move there
		UE_LOG(LogTemp, Warning, TEXT("No Trace Hit"));
		//add the position that has no overlaps to movementPoints
		if(Attacking == false)
		{
			MovementPoints.Push(OriginalMovePoint);
		}
		

		//Until we have enough movement pointw for the amount of unit selected, keep checking
		while (MovementPoints.Num() != CurrentController->UnitList.Num() && single == false || MovementPoints.Num() != 1 && single == true)
		{
			//reset mouse2 position to orginal mouse position
			MovePoint = OriginalMovePoint;

			//Check whuch move position we checking
			switch (RadiusCheck)
			{
				//Check for above posistion is clear
			case 0:
				// add the radious change amount to  the X pos
				MovePoint.X += RadiusChangeAmount;
				//create a debug sphere and check if there an overlap in that position
				DrawDebugSphere(World->GetWorld(), MovePoint, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
				if (!World->GetWorld()->SweepSingleByChannel(RV_Hit, MovePoint, FVector(MovePoint.X, MovePoint.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape))
				{
					//if no overlap that means it clear and push the mouse position 2 to movement points
					MovementPoints.Push(MovePoint);
				}
				RadiusCheck++;
				break;
				////Check for Bottom posistion is clear
			case 1:
				MovePoint.X -= RadiusChangeAmount;
				//create a debug sphere and check if there an overlap in that position
				DrawDebugSphere(World->GetWorld(), MovePoint, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
				if (!World->GetWorld()->SweepSingleByChannel(RV_Hit, MovePoint, FVector(MovePoint.X, MovePoint.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape))
				{
					//if no overlap that means it clear and push the mouse position 2 to movement points
					MovementPoints.Push(MovePoint);
				}
				RadiusCheck++;
				break;
				////Check for right posistion is clear
			case 2:
				MovePoint.Y += RadiusChangeAmount;
				//create a debug sphere and check if there an overlap in that position
				DrawDebugSphere(World->GetWorld(), MovePoint, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
				if (!World->GetWorld()->SweepSingleByChannel(RV_Hit, MovePoint, FVector(MovePoint.X, MovePoint.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape))
				{
					//if no overlap that means it clear and push the mouse position 2 to movement points
					MovementPoints.Push(MovePoint);
				}
				RadiusCheck++;
				break;
				////Check for Left posistion is clear
			case 3:
				MovePoint.Y -= RadiusChangeAmount;
				//create a debug sphere and check if there an overlap in that position
				DrawDebugSphere(World->GetWorld(), MovePoint, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
				if (!World->GetWorld()->SweepSingleByChannel(RV_Hit, MovePoint, FVector(MovePoint.X, MovePoint.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape))
				{
					//if no overlap that means it clear and push the mouse position 2 to movement points
					MovementPoints.Push(MovePoint);
				}
				RadiusCheck++;
				break;
				////Check for Top Right posistion is clear
			case 4:
				MovePoint.X += RadiusChangeAmount;
				MovePoint.Y -= RadiusChangeAmount;

				//create a debug sphere and check if there an overlap in that position
				DrawDebugSphere(World->GetWorld(), MovePoint, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
				if (!World->GetWorld()->SweepSingleByChannel(RV_Hit, MovePoint, FVector(MovePoint.X, MovePoint.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape))
				{
					//if no overlap that means it clear and push the mouse position 2 to movement points
					MovementPoints.Push(MovePoint);
				}
				RadiusCheck++;
				break;

				////Check for Top Left posistion is clear
			case 5:
				MovePoint.X += RadiusChangeAmount;
				MovePoint.Y += RadiusChangeAmount;
				//create a debug sphere and check if there an overlap in that position
				DrawDebugSphere(World->GetWorld(), MovePoint, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
				if (!World->GetWorld()->SweepSingleByChannel(RV_Hit, MovePoint, FVector(MovePoint.X, MovePoint.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape))
				{
					//if no overlap that means it clear and push the mouse position 2 to movement points
					MovementPoints.Push(MovePoint);
				}
				RadiusCheck++;
				break;
				////Check for Bottom Left posistion is clear
			case 6:
				MovePoint.X -= RadiusChangeAmount;
				MovePoint.Y -= RadiusChangeAmount;
				//create a debug sphere and check if there an overlap in that position
				DrawDebugSphere(World->GetWorld(), MovePoint, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
				if (!World->GetWorld()->SweepSingleByChannel(RV_Hit, MovePoint, FVector(MovePoint.X, MovePoint.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape))
				{
					//if no overlap that means it clear and push the mouse position 2 to movement points
					MovementPoints.Push(MovePoint);
				}
				RadiusCheck++;
				break;
			case 7:
				MovePoint.X -= RadiusChangeAmount;
				MovePoint.Y += RadiusChangeAmount;

				//create a debug sphere and check if there an overlap in that position
				DrawDebugSphere(World->GetWorld(), MovePoint, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
				if (!World->GetWorld()->SweepSingleByChannel(RV_Hit, MovePoint, FVector(MovePoint.X, MovePoint.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape))
				{
					//if no overlap that means it clear and push the mouse position 2 to movement points
					MovementPoints.Push(MovePoint);
				}
				RadiusCheck++;
				break;
				// if we have check all move position, increase the radius and set radious check to 0
				//check again with an increase radius
			case 8:
				RadiusCheck = 0;
				RadiusChangeAmount += RadiusChangeAmount;
				break;

			default:
				break;
			}

		}
	}
	//return MovementPoints
	return MovementPoints;
}



//make make in own function that takes permaters so isntead of two fundtions that simlair just one
TArray<FVector> UFunctionLibrary::CheckSingleTarget(ARTSPlayerController* CurrentController, float RadiusChangeAmount, float SphereRadius, FVector Position, bool Attacking, UWorld* World, bool single)
{
	// do we need to increase the radius check
	bool IncreaseRaduius = false;
	//int to count how many radius checks have been made, after 8 it increase the radius
	int RadiusCheck = 0;
	FHitResult RV_Hit;

	//FVector Tarray , use to store location of the move points
	TArray<FVector> MovementPoints;
	//get the mouse position
	FVector OriginalMovePoint = Position;
	//set z to 0 as we can ingore that value
	OriginalMovePoint.Z = 0.0f;
	//Second mouse position set it to the , mouse position
	FVector MovePoint = OriginalMovePoint;
	//Re-initialize hit info
	RV_Hit.Init();
	//Coolision shape info
	FCollisionShape Shape;
	Shape.SetSphere(SphereRadius);
	//float for raduous change amount


	//Draw a debug sphere
	DrawDebugSphere(World->GetWorld(), OriginalMovePoint, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
	//Create a sweep single by chaneel to check if the mouse position is empty, no overlapping actors
	if (World->GetWorld()->SweepSingleByChannel(RV_Hit, OriginalMovePoint, FVector(OriginalMovePoint.X, OriginalMovePoint.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape) || Attacking == true)
	{
		
		//if no actors are hit we can move there
		UE_LOG(LogTemp, Warning, TEXT("No Trace Hit"));
		//add the position that has no overlaps to movementPoints
		if (Attacking == false)
		{
			MovementPoints.Push(OriginalMovePoint);
		}


		//Until we have enough movement pointw for the amount of unit selected, keep checking
		while (MovementPoints.Num() != CurrentController->UnitList.Num() && single == false || MovementPoints.Num() != 1 && single == true)
		{
			//reset mouse2 position to orginal mouse position
			MovePoint = OriginalMovePoint;

			//Check whuch move position we checking
			switch (RadiusCheck)
			{
				//Check for above posistion is clear
			case 0:
				// add the radious change amount to  the X pos
				MovePoint.X += RadiusChangeAmount;
				//create a debug sphere and check if there an overlap in that position
				DrawDebugSphere(World->GetWorld(), MovePoint, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
				if (!World->GetWorld()->SweepSingleByChannel(RV_Hit, MovePoint, FVector(MovePoint.X, MovePoint.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape))
				{
					//if no overlap that means it clear and push the mouse position 2 to movement points
					MovementPoints.Push(MovePoint);
				}
				RadiusCheck++;
				break;
				////Check for Bottom posistion is clear
			case 1:
				MovePoint.X -= RadiusChangeAmount;
				//create a debug sphere and check if there an overlap in that position
				DrawDebugSphere(World->GetWorld(), MovePoint, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
				if (!World->GetWorld()->SweepSingleByChannel(RV_Hit, MovePoint, FVector(MovePoint.X, MovePoint.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape))
				{
					//if no overlap that means it clear and push the mouse position 2 to movement points
					MovementPoints.Push(MovePoint);
				}
				RadiusCheck++;
				break;
				////Check for right posistion is clear
			case 2:
				MovePoint.Y += RadiusChangeAmount;
				//create a debug sphere and check if there an overlap in that position
				DrawDebugSphere(World->GetWorld(), MovePoint, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
				if (!World->GetWorld()->SweepSingleByChannel(RV_Hit, MovePoint, FVector(MovePoint.X, MovePoint.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape))
				{
					//if no overlap that means it clear and push the mouse position 2 to movement points
					MovementPoints.Push(MovePoint);
				}
				RadiusCheck++;
				break;
				////Check for Left posistion is clear
			case 3:
				MovePoint.Y -= RadiusChangeAmount;
				//create a debug sphere and check if there an overlap in that position
				DrawDebugSphere(World->GetWorld(), MovePoint, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
				if (!World->GetWorld()->SweepSingleByChannel(RV_Hit, MovePoint, FVector(MovePoint.X, MovePoint.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape))
				{
					//if no overlap that means it clear and push the mouse position 2 to movement points
					MovementPoints.Push(MovePoint);
				}
				RadiusCheck++;
				break;
				////Check for Top Right posistion is clear
			case 4:
				MovePoint.X += RadiusChangeAmount;
				MovePoint.Y -= RadiusChangeAmount;

				//create a debug sphere and check if there an overlap in that position
				DrawDebugSphere(World->GetWorld(), MovePoint, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
				if (!World->GetWorld()->SweepSingleByChannel(RV_Hit, MovePoint, FVector(MovePoint.X, MovePoint.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape))
				{
					//if no overlap that means it clear and push the mouse position 2 to movement points
					MovementPoints.Push(MovePoint);
				}
				RadiusCheck++;
				break;

				////Check for Top Left posistion is clear
			case 5:
				MovePoint.X += RadiusChangeAmount;
				MovePoint.Y += RadiusChangeAmount;
				//create a debug sphere and check if there an overlap in that position
				DrawDebugSphere(World->GetWorld(), MovePoint, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
				if (!World->GetWorld()->SweepSingleByChannel(RV_Hit, MovePoint, FVector(MovePoint.X, MovePoint.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape))
				{
					//if no overlap that means it clear and push the mouse position 2 to movement points
					MovementPoints.Push(MovePoint);
				}
				RadiusCheck++;
				break;
				////Check for Bottom Left posistion is clear
			case 6:
				MovePoint.X -= RadiusChangeAmount;
				MovePoint.Y -= RadiusChangeAmount;
				//create a debug sphere and check if there an overlap in that position
				DrawDebugSphere(World->GetWorld(), MovePoint, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
				if (!World->GetWorld()->SweepSingleByChannel(RV_Hit, MovePoint, FVector(MovePoint.X, MovePoint.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape))
				{
					//if no overlap that means it clear and push the mouse position 2 to movement points
					MovementPoints.Push(MovePoint);
				}
				RadiusCheck++;
				break;
			case 7:
				MovePoint.X -= RadiusChangeAmount;
				MovePoint.Y += RadiusChangeAmount;

				//create a debug sphere and check if there an overlap in that position
				DrawDebugSphere(World->GetWorld(), MovePoint, Shape.GetSphereRadius(), 4, FColor::Green, true, 2.f, false, 4.f);
				if (!World->GetWorld()->SweepSingleByChannel(RV_Hit, MovePoint, FVector(MovePoint.X, MovePoint.Y, 1000.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f), ECC_Pawn, Shape))
				{
					//if no overlap that means it clear and push the mouse position 2 to movement points
					MovementPoints.Push(MovePoint);
				}
				RadiusCheck++;
				break;
				// if we have check all move position, increase the radius and set radious check to 0
				//check again with an increase radius
			case 8:
				RadiusCheck = 0;
				RadiusChangeAmount += RadiusChangeAmount;
				break;

			default:
				break;
			}

		}
	}

	//return MovementPoints
	return MovementPoints;
}