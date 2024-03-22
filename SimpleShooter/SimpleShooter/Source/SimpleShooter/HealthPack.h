// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableItem.h"
#include "HealthPack.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AHealthPack : public APickableItem
{
	GENERATED_BODY()

protected:
	virtual bool PickUpItem(AShooterCharacter* Character) override;
};
