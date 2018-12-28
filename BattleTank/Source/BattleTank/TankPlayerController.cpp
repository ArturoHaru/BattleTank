// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#define OUT

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessinng a Tank"))
	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *ControlledTank->GetName())
	}
}


void ATankPlayerController::Tick( float DeltaTime ) {

	Super::Tick( DeltaTime );
	//Start the barrel moving towards so the
	//shot hit where the crosshair intersects the world
	AimTowardsCrosshair();

}




ATank* ATankPlayerController::GetControlledTank() const{

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //Out Parameter
	
	if (GetSightRayHitLocation(HitLocation)) { //Has side-effect, is going to line-trace
		 UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s "), *HitLocation.ToString());
			//TODO Tell controlled tank to aim at this point
	}
}


//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {

	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);


	//"De-project" the screen position of the crosshair to a world direction 
	FVector LookDirection;
	if(GetLookDirection(ScreenLocation, OUT LookDirection))
	{
		//Line trace long that LookDirection, and see what we hit

		GetLookVectorHitDirection(LookDirection, HitLocation);
	
		//UE_LOG(LogTemp, Warning, TEXT("You are looking: %s"), *LookDirection.ToString());
	}

	
	return true;

}

bool ATankPlayerController::GetLookVectorHitDirection(FVector LookDirection, FVector& HitLocation) const {

	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

		if (GetWorld()->LineTraceSingleByChannel(
			OUT HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility
		)) {

			HitLocation = HitResult.Location;
			return true;
		}
	HitLocation = FVector(0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& WorldDirection) const {

	FVector WorldLocation; //To discarge

	return DeprojectScreenPositionToWorld(

		ScreenLocation.X,
		ScreenLocation.Y,
		OUT WorldLocation,
		OUT WorldDirection
	);

		

	


}