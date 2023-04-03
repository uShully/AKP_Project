// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AKP_Project.h"
#include "GameFramework/Actor.h"
#include "InterActiveInterface.h"
#include "InteractiveObject.generated.h"

UCLASS()
class AKP_PROJECT_API AInteractiveObject : public AActor, public IInterActiveInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	

	class AAKPGameMode* gameMode;

	
	AActor* InterActivePlayerCharacter;


public:	
	virtual void InteractPure() override;


	

};
