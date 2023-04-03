// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AKP_Project.h"
#include "Components/ActorComponent.h"
#include "CharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AKP_PROJECT_API UCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStatComponent();

	FTimerHandle StaminaRegeneration;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

	void RegenerateStamina();

public:	
	void SetNewCharacterStat(int32 NewCharacterNum);
	void SetNewEnemyCharacterStat();
	void SetHP(float NewHP);
	void SetStamina(float NewStamina);
	void SetDamage(float NewDamage); // º¯°æ
	void SetDefense(float NewDefense) { CurrentDefenseValue = NewDefense; };
	void SetVigor(int32 NewVigor);
	void SetEndurance(int32 NewEndurance);
	void SetStrength(int32 NewStrength);
	void SetVitality(int32 NewVitality);

	float GetAttack();

	float GetMaxStamina();
	float GetMaxHP();

	UFUNCTION(BlueprintCallable, Category = "Stat")
	float GetHPRatio();	
	UFUNCTION(BlueprintCallable, Category = "Stat")
	float GetStaminaRatio();

	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangedDelegate OnHPChanged;

	int32 GetCurrentLevel() { return Level; };
	float GetCurrentHP() {	return CurrentHP;};
	int32 GetCurrentVigor() { return CurrentVigor; };
	int32 GetCurrentEndurance() { return CurrentEndurance; };
	int32 GetCurrentStrength() { return CurrentStrength; };
	int32 GetCurrentVitality() { return CurrentVitality; };
	

	
	
	
private:
	struct FAKPCharacterData* CurrentStatData = nullptr;
	struct FAKPCharacterStatData* StatIncreaseData = nullptr;


	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 CharacterNum;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 Level;
	UPROPERTY(Transient, VisibleInstanceOnly , Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentHP;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentStamina;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentAttackValue;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentStrengthAttackValue;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentWeaponAttackValue;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentDefenseValue;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentVitalityDefenseValue;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentAmmoDefenseValue;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 CurrentVigor;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 CurrentEndurance;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 CurrentStrength;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 CurrentVitality;
};
