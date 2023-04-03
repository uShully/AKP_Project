// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatComponent.h"
#include "AKP_ProjectCharacter.h"
#include "EnemyBaseCharacter.h"
#include "AKPGameInstance.h"

// Sets default values for this component's properties
UCharacterStatComponent::UCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	// ...

	CharacterNum = 0;
}


// Called when the game starts
void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	auto owner = GetOwner();
	// ...
	if (owner == Cast<AAKP_ProjectCharacter>(owner))
	GetWorld()->GetTimerManager().SetTimer(StaminaRegeneration, this, &UCharacterStatComponent::RegenerateStamina, 1.f, true);
}


// Called every frame
void UCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	auto owner = GetOwner();
	
	if (owner == Cast<AAKP_ProjectCharacter>(owner))
		SetNewCharacterStat(CharacterNum);
	else if (owner == Cast<AEnemyBaseCharacter>(owner))
		SetNewEnemyCharacterStat();
}

void UCharacterStatComponent::SetNewCharacterStat(int32 NewCharacterNum)
{
	auto AKPGameInstance = Cast<UAKPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	AKPCHECK(nullptr != AKPGameInstance);
	CurrentStatData = AKPGameInstance->GetAKPCharacterData(CharacterNum);
		if (nullptr != CurrentStatData) {
			Level = CurrentStatData->Level;
			SetHP(CurrentStatData->MaxHP);
			CurrentStamina = 0.f;

			SetVitality(CurrentStatData->Vitality);
			SetEndurance(CurrentStatData->Endurance);
			SetStrength(CurrentStatData->Strength);
			SetVigor(CurrentStatData->Vigor);
			
		}
		else
		{
			AKPLOG(Error, TEXT("Level (%d) data doesnt't exist"), NewCharacterNum);
		}
}

void UCharacterStatComponent::SetNewEnemyCharacterStat()
{
	SetHP(500);
}

void UCharacterStatComponent::SetDamage(float NewDamage)
{
	auto owner = GetOwner();

	if (owner == Cast<AAKP_ProjectCharacter>(owner))
		SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.f, CurrentStatData->MaxHP));
	else if (owner == Cast<AEnemyBaseCharacter>(owner))
		SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.f, 500.f));

}

void UCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
		if (CurrentHP < KINDA_SMALL_NUMBER)
		{
			CurrentHP = 0.f;
			OnHPIsZero.Broadcast();
		}
}

void UCharacterStatComponent::SetStamina(float NewStamina)
{
	CurrentStamina = NewStamina;
}

float UCharacterStatComponent::GetAttack()
{
	return (100 * (CurrentStrengthAttackValue/100)) ;
}

float UCharacterStatComponent::GetMaxHP()
{
	return CurrentStatData->MaxHP;
}

float UCharacterStatComponent::GetHPRatio()
{
	AKPCHECK(nullptr != CurrentStatData, 0.f);

	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
}

float UCharacterStatComponent::GetMaxStamina()
{
	return 100.f; // MaxStamina
}

float UCharacterStatComponent::GetStaminaRatio()
{
	return (CurrentStamina < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentStamina / 100.f);
}

void UCharacterStatComponent::RegenerateStamina()
{
	if (CurrentStamina >= 100.f)
		CurrentStamina = 100.f;
	else
		++CurrentStamina;
}

void UCharacterStatComponent::SetVigor(int32 NewVigor)
{
	auto AKPGameInstance = Cast<UAKPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	int32 totalVigor = 0;


	for (int32 i = 1; i <= NewVigor; i++) {
		StatIncreaseData = AKPGameInstance->GetAKPStatIncreaseData(i);
		totalVigor += StatIncreaseData->VigorIncreaseValue;
	}

	CurrentVigor = NewVigor;
}

void UCharacterStatComponent::SetEndurance(int32 NewEndurance)
{
	auto AKPGameInstance = Cast<UAKPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	int32 totalEndurance = 0;


	for (int32 i = 1; i <= NewEndurance; i++) {
		StatIncreaseData = AKPGameInstance->GetAKPStatIncreaseData(i);
		totalEndurance += StatIncreaseData->EnduranceIncreaseValue;
	}

	CurrentEndurance = NewEndurance;
}

void UCharacterStatComponent::SetStrength(int32 NewStrength)
{
	auto AKPGameInstance = Cast<UAKPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	int32 totalStrength = 0;


	for (int32 i = 1; i <= NewStrength; i++) {
		StatIncreaseData = AKPGameInstance->GetAKPStatIncreaseData(i);
		totalStrength += StatIncreaseData->StrengthIncreaseValue;
	}

	CurrentStrength = NewStrength;
	CurrentStrengthAttackValue = totalStrength;
}

void UCharacterStatComponent::SetVitality(int32 NewVitality)
{
	auto AKPGameInstance = Cast<UAKPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	int32 totalVitality = 0;


	for (int32 i = 1; i <= NewVitality; i++) {
		StatIncreaseData = AKPGameInstance->GetAKPStatIncreaseData(i);
		totalVitality += StatIncreaseData->VitalityIncreaseValue;
	}

	CurrentVitality = NewVitality;
}