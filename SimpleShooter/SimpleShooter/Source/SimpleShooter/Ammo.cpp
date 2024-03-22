// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo.h"
#include "ShooterCharacter.h"
#include "Gun.h"

bool AAmmo::PickUpItem(AShooterCharacter* Character)
{
	bool basePicked = Super::PickUpItem(Character);

	AGun* Gun = Character->GetGun(GunType);
	if (Gun && !Gun->IsFullOfAmmo())
	{
		Gun->AddAmmo(Amount);
		return true && basePicked;
	}

	return false;
}
