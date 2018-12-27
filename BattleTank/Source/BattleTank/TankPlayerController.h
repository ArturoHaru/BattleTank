// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ATank * GetControlledTank() const;
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void AimTowardsCrosshair();

	// Return an  OUT parameter, true if hits landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;
};
