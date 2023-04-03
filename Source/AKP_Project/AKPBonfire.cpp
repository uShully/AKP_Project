// Fill out your copyright notice in the Description page of Project Settings.


#include "AKPBonfire.h"
#include "AKPGameMode.h"

AAKPBonfire::AAKPBonfire()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_MESH(TEXT("StaticMesh'/Game/InfinityBladeFireLands/Environments/Forge/Env_Forge/StaticMesh/SM_Anvil_1.SM_Anvil_1'"));
	if (SM_MESH.Succeeded()) {
		Mesh->SetStaticMesh(SM_MESH.Object);
	}

	gameMode = nullptr;
}

void AAKPBonfire::BeginPlay()
{
	Super::BeginPlay();

	gameMode = Cast<AAKPGameMode>(GetWorld()->GetAuthGameMode());
}

void AAKPBonfire::InteractPure()
{
	gameMode->AddToViewBonfireInterActiveWidget();
	gameMode->SetControllerwhileUIActive(true);
}
