// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AKP_Project.h"
#include "GameFramework/PlayerController.h"
#include "AKPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AKP_PROJECT_API AAKPPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void BeginPlay() override;

};
