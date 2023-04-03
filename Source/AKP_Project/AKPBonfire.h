// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject.h"
#include "AKPBonfire.generated.h"

/**
 * 
 */
UCLASS()
class AKP_PROJECT_API AAKPBonfire : public AInteractiveObject
{
	GENERATED_BODY()

public:

	AAKPBonfire();

protected:

	virtual void BeginPlay() override;


public:
	UPROPERTY(VisibleAnywhere, Category = "NPC")
		UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = "NPC")
		UStaticMeshComponent* Mesh;

	virtual void InteractPure() override;
};
