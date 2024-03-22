// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	bool CanHeal();
	void Heal(int Amount);

	UFUNCTION(BlueprintPure)
	bool IsDead() const;
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	void Shoot();
	UFUNCTION(BlueprintPure)
	AGun* GetGun(TSubclassOf<AGun> GunType) const;
	UFUNCTION(BlueprintPure)
	TSubclassOf<AGun> GetActiveGunType() const;

private:
	UPROPERTY(EditAnywhere)
	float RotationRate = 10;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AGun>> GunClasses;
	UPROPERTY()
	TArray<AGun*> Guns;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;
	UPROPERTY(VisibleAnywhere)
	float Health;

	int32 ActiveIndex;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	//void LookUp(float AxisValue);
	void ControllerLookUp(float AxisValue);
	void ControllerLookRight(float AxisValue);
	void SwitchWeapon(float AxisValue);
};
