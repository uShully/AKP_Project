// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "AKPAIController.h"
#include "AKP_ProjectCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 600.f;

	if (nullptr == World) return;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	if (bResult) {
		for (auto OverlapResult : OverlapResults) {
			AAKP_ProjectCharacter* AKPCharacter = Cast<AAKP_ProjectCharacter>(OverlapResult.GetActor());
			if (AKPCharacter && AKPCharacter->GetController()->IsPlayerController()) {
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AAKPAIController::TargetKey, AKPCharacter);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(World, AKPCharacter->GetActorLocation(), 10.f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), AKPCharacter->GetActorLocation(), FColor::Blue, false, 0.2f);
				return;
			}
		}
	}
	else {
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AAKPAIController::TargetKey, nullptr);
	}
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}