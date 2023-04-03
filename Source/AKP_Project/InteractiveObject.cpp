// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject.h"
#include "AKP_ProjectCharacter.h"
#include "AKPGameMode.h"

// Sets default values
AInteractiveObject::AInteractiveObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	gameMode = nullptr;
	InterActivePlayerCharacter = nullptr;
}

// Called when the game starts or when spawned
void AInteractiveObject::BeginPlay()
{
	Super::BeginPlay();
	
	gameMode = Cast<AAKPGameMode>(GetWorld()->GetAuthGameMode());
}

void AInteractiveObject::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AKPLOG(Warning, TEXT("BeginOverlap"));
	if (OtherActor == Cast<AAKP_ProjectCharacter>(OtherActor)) {
		gameMode->AddToViewInterActiveWidget();
		Cast<AAKP_ProjectCharacter>(OtherActor)->SetCurrentInterActiveActor(this);
		InterActivePlayerCharacter = OtherActor;
	}
}

void AInteractiveObject::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	AKPLOG(Warning, TEXT("EndOverlap"));
	if (OtherActor == Cast<AAKP_ProjectCharacter>(OtherActor)) {
		gameMode->RemoveWidgetFromViewPort();
		Cast<AAKP_ProjectCharacter>(OtherActor)->SetCurrentInterActiveActor(nullptr);
		InterActivePlayerCharacter = nullptr;
	}
}

void AInteractiveObject::InteractPure()
{
	

}

