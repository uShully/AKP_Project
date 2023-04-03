// Fill out your copyright notice in the Description page of Project Settings.


#include "AKPItemBox.h"
#include "UObject/ConstructorHelpers.h"
#include "AKP_ProjectCharacter.h"
#include "AKPGameMode.h"
// Sets default values
AAKPItemBox::AAKPItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("StaticMesh'/Game/InfinityBladeFireLands/Environments/Forge/Env_Forge/StaticMesh/SM_Forge_Chest_Bottom.SM_Forge_Chest_Bottom'"));
	if (SM_BOX.Succeeded()) {
		Box->SetStaticMesh(SM_BOX.Object);
	}

	gameMode = nullptr;

}

void AAKPItemBox::BeginPlay()
{
	Super::BeginPlay();


}

void AAKPItemBox::InteractPure()
{
	Cast<AAKP_ProjectCharacter>(InterActivePlayerCharacter)->SetCurrentInterActiveActor(nullptr);
	Destroy();
}
