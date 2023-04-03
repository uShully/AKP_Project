// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingItem.h"
#include "AKP_ProjectCharacter.h"
#include "CharacterStatComponent.h"

void UHealingItem::Use(class AAKP_ProjectCharacter* Character)
{
	if (Character)	{
		Character->CharacterStat->SetHP(Character->CharacterStat->GetCurrentHP() + HealthToHeal);
	}
}