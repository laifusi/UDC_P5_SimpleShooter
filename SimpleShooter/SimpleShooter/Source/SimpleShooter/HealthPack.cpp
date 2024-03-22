// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"
#include "ShooterCharacter.h"

bool AHealthPack::PickUpItem(AShooterCharacter* Character)
{
	if (Character->CanHeal())
	{
		Character->Heal(Amount);
		return true;
	}
	else
	{
		return false;
	}
}
