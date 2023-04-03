// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnToTarget.h"
#include "AKPAIController.h"
#include "EnemyBaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AKP_ProjectCharacter.h"


UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto EnemyCharacter = Cast<AEnemyBaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == EnemyCharacter)
		return EBTNodeResult::Failed;

	auto Target = Cast<AAKP_ProjectCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AAKPAIController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - EnemyCharacter->GetActorLocation();
	LookVector.Z = 0.f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	EnemyCharacter->SetActorRotation(FMath::RInterpTo(EnemyCharacter->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.f));

	return EBTNodeResult::Succeeded;
}