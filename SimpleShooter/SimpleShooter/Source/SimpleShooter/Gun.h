// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();
	bool HasAmmo() const;
	bool IsFullOfAmmo() const;
	void AddAmmo(int Amount);

	UFUNCTION(BlueprintPure)
	int GetCurrentAmmo() const;
	UFUNCTION(BlueprintPure)
	int GetMaxAmmo() const;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitParticles;
	UPROPERTY(EditAnywhere)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	UPROPERTY(EditAnywhere, Category="Ammo")
	int InitialAmmo;
	UPROPERTY(VisibleAnywhere, Category = "Ammo")
	int CurrentAmmo;
	UPROPERTY(EditAnywhere, Category = "Ammo")
	int MaxAmmo = 10;
	UPROPERTY(EditAnywhere, Category = "Ammo")
	USoundBase* OutOfAmmoSound;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);
	AController* GetOwnerController() const;

};
