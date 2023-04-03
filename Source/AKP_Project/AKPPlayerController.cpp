// Fill out your copyright notice in the Description page of Project Settings.


#include "AKPPlayerController.h"

void AAKPPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AKPLOG_S(Warning);
}

void AAKPPlayerController::OnPossess(APawn* aPawn)
{
	AKPLOG_S(Warning);
	Super::OnPossess(aPawn);
	
}

void AAKPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	

}