// Fill out your copyright notice in the Description page of Project Settings.


#include "AKPNPC.h"
#include "AKPGameMode.h"

AAKPNPC::AAKPNPC()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_MESH(TEXT("StaticMesh'/Game/InfinityBladeFireLands/Environments/Forge/Env_Forge/StaticMesh/SM_Forge_Chest_Bottom.SM_Forge_Chest_Bottom'"));
	if (SM_MESH.Succeeded()) {
		Mesh->SetStaticMesh(SM_MESH.Object);
	}

	gameMode = nullptr;
}

void AAKPNPC::BeginPlay()
{
	Super::BeginPlay();

	gameMode = Cast<AAKPGameMode>(GetWorld()->GetAuthGameMode());
}

void AAKPNPC::InteractPure()
{
	gameMode->AddToViewNPCInterActiveWidget();
}