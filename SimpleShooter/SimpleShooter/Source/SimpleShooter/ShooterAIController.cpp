// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Testing AAIController methods
	/*APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if (LineOfSightTo(PlayerPawn))
	{
		MoveToActor(PlayerPawn, AcceptanceRadius);
		SetFocus(PlayerPawn);
	}
	else
	{
		StopMovement();
		ClearFocus(EAIFocusPriority::Gameplay);
	}*/
}

bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if (ControlledCharacter)
	{
		return ControlledCharacter->IsDead();
	}

	return true;
}


