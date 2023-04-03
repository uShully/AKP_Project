// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AKP_Project.h"
#include "AIController.h"
#include "AKPAIController.generated.h"

/**
 * 
 */
UCLASS()
class AKP_PROJECT_API AAKPAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAKPAIController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
private:
	UPROPERTY()
		class UBehaviorTree* BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;
	

};
