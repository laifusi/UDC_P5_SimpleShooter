// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* OwnerController = OwnerComp.GetAIOwner();

	if (OwnerController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	APawn* OwnerPawn = OwnerController->GetPawn();
	AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(OwnerPawn);

	if (OwnerPawn == nullptr || ShooterCharacter == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ShooterCharacter->Shoot();

	return EBTNodeResult::Succeeded;
}
