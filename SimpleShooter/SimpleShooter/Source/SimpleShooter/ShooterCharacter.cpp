// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	ActiveIndex = 0;
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	for (int i = 0; i < GunClasses.Num(); i++)
	{
		Guns.Add(GetWorld()->SpawnActor<AGun>(GunClasses[i]));
		Guns[i]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		Guns[i]->SetOwner(this);
		Guns[i]->SetActorHiddenInGame(ActiveIndex != i);
	}

	Health = MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("ControllerLookUp"), this, &AShooterCharacter::ControllerLookUp);
	PlayerInputComponent->BindAxis(TEXT("ControllerLookRight"), this, &AShooterCharacter::ControllerLookRight);
	PlayerInputComponent->BindAxis(TEXT("SwitchWeapon"), this, &AShooterCharacter::SwitchWeapon);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

	if (IsDead())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

bool AShooterCharacter::CanHeal()
{
	return Health < MaxHealth;
}

void AShooterCharacter::Heal(int Amount)
{
	Health += Amount;
	if (Health > MaxHealth)
	{
		Health = MaxHealth;
	}
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

/*void AShooterCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}*/

void AShooterCharacter::ControllerLookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::ControllerLookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::SwitchWeapon(float AxisValue)
{
	ActiveIndex += AxisValue;
	if (ActiveIndex >= GunClasses.Num())
	{
		ActiveIndex = 0;
	}
	else if (ActiveIndex < 0)
	{
		ActiveIndex = GunClasses.Num() - 1;
	}

	for (int i = 0; i < GunClasses.Num(); i++)
	{
		Guns[i]->SetActorHiddenInGame(ActiveIndex != i);
	}
}

void AShooterCharacter::Shoot()
{
	Guns[ActiveIndex]->PullTrigger();
}

AGun* AShooterCharacter::GetGun(TSubclassOf<AGun> GunType) const
{
	for (AGun* Gun : Guns)
	{
		if (Gun->GetClass() == GunType)
			return Gun;
	}
	return nullptr;
}

TSubclassOf<AGun> AShooterCharacter::GetActiveGunType() const
{
	return Guns[ActiveIndex]->GetClass();
}

