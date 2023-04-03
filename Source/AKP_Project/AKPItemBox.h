// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractiveObject.h"
#include "AKPItemBox.generated.h"

UCLASS()
class AKP_PROJECT_API AAKPItemBox : public AInteractiveObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAKPItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	UPROPERTY(VisibleAnywhere, Category = Box)
		UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = Box)
		UStaticMeshComponent* Box;

	virtual void InteractPure() override;
};
