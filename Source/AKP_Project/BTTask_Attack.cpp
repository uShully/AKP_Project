// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "AKPAIController.h"
#include "EnemyBaseCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	auto EnemyBaseCharacter = Cast<AEnemyBaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == EnemyBaseCharacter)
		return EBTNodeResult::Failed;
	
	EnemyBaseCharacter->Attack();
	IsAttacking = true;
	EnemyBaseCharacter->OnAttackEnd.AddLambda([this]() -> void{
		IsAttacking = false;
	});
	
	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if(!IsAttacking) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}