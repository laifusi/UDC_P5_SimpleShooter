#include "PickableItem.h"
// Fill out your copyright notice in the Description page of Project Settings.

#include "PickableItem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickableItem::APickableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ColliderComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(ColliderComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(ColliderComp);
}

// Called when the game starts or when spawned
void APickableItem::BeginPlay()
{
	Super::BeginPlay();
	
	ColliderComp->OnComponentBeginOverlap.AddDynamic(this, &APickableItem::OnActorOverlap);
}

// Called every frame
void APickableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickableItem::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bool pickedUp = false;

	AShooterCharacter* Character = Cast<AShooterCharacter>(OtherActor);
	if (Character && Cast<APlayerController>(Character->GetController()))
	{
		pickedUp = PickUpItem(Character);
	}

	if (pickedUp)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, PickUpSound, GetActorLocation());
		Destroy();
	}
	else
	{
		UGameplayStatics::SpawnSoundAtLocation(this, CantPickSound, GetActorLocation());
	}
}

bool APickableItem::PickUpItem(AShooterCharacter* Character)
{
	return true;
}

