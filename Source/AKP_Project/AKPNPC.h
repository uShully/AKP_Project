// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AKP_Project.h"
#include "InteractiveObject.h"
#include "AKPNPC.generated.h"

/**
 * 
 */
UCLASS()
class AKP_PROJECT_API AAKPNPC : public AInteractiveObject
{
	GENERATED_BODY()
public:

		AAKPNPC();

protected:

	virtual void BeginPlay() override;


public:
	UPROPERTY(VisibleAnywhere, Category = "NPC")
		UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = "NPC")
		UStaticMeshComponent* Mesh;

	virtual void InteractPure() override;
};
