// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableItem.h"
#include "Ammo.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AAmmo : public APickableItem
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun> GunType;

protected:
	virtual bool PickUpItem(AShooterCharacter* Character) override;
};
