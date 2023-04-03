// Fill out your copyright notice in the Description page of Project Settings.


#include "AKPWeapon.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AAKPWeapon::AAKPWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	RootComponent = Weapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("SkeletalMesh'/Game/Weapon_Pack/Skeletal_Mesh/SK_GreatAxe.SK_GreatAxe'"));
	if (SK_WEAPON.Succeeded()) {
		Weapon->SetSkeletalMesh(SK_WEAPON.Object);
	}
	
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));

}

// Called when the game starts or when spawned
void AAKPWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


