 //// Fill out your copyright notice in the Description page of Project Settings.


#include "AKPAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AAKPAIController::HomePosKey(TEXT("HomePos"));
const FName AAKPAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AAKPAIController::TargetKey(TEXT("Target"));

AAKPAIController::AAKPAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/BehaviorTree/BB_EnemyCharacter.BB_EnemyCharacter'"));
	if (BBObject.Succeeded()) {
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/BehaviorTree/BT_EnemyCharacter.BT_EnemyCharacter'"));
	if (BTObject.Succeeded()) {
		BTAsset = BTObject.Object;
	}

}

void AAKPAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &AAKPAIController::OnRepeatTimer, RepeatInterval, true);
	if (UseBlackboard(BBAsset, Blackboard)) {
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset)) {
			AKPLOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}

}

void AAKPAIController::OnUnPossess()
{
	Super::OnUnPossess();
	//GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

