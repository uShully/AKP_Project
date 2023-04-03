// Fill out your copyright notice in the Description page of Project Settings.


#include "GrowthWidget.h"
#include "Components/TextBlock.h"
#include "AKP_ProjectCharacter.h"
#include "CharacterStatComponent.h"

void UGrowthWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LevelNum = Cast<UTextBlock>(GetWidgetFromName(TEXT("LevelNum")));
	CurrentVigorNum = Cast<UTextBlock>(GetWidgetFromName(TEXT("CurrentVigorNum")));
	CurrentStrengthNum = Cast<UTextBlock>(GetWidgetFromName(TEXT("CurrentStrengthNum")));

	ReflashText();
}

void UGrowthWidget::ReflashText()
{
	auto Owner = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (nullptr != Owner) {
		CurrentLV = Cast<AAKP_ProjectCharacter>(Owner)->CharacterStat->GetCurrentLevel();

		CurrentMaxHP = Cast<AAKP_ProjectCharacter>(Owner)->CharacterStat->GetMaxHP();
		CurrentMaxStamina = Cast<AAKP_ProjectCharacter>(Owner)->CharacterStat->GetMaxStamina();
		
		CurrentVigor = Cast<AAKP_ProjectCharacter>(Owner)->CharacterStat->GetCurrentVigor();
		CurrentEndurance = Cast<AAKP_ProjectCharacter>(Owner)->CharacterStat->GetCurrentEndurance();
		CurrentSTR = Cast<AAKP_ProjectCharacter>(Owner)->CharacterStat->GetCurrentStrength();
		CurrentVitality = Cast<AAKP_ProjectCharacter>(Owner)->CharacterStat->GetCurrentVitality();

		tempChangeVigor = CurrentVigor;
		tempChangeEndurance = CurrentEndurance;
		tempChangeSTR = CurrentSTR;
		tempChangeVitality = CurrentVitality;
		
		CurrentDamage = Cast<AAKP_ProjectCharacter>(Owner)->CharacterStat->GetAttack();



		LevelNum->SetText(FText::FromString(FString::Printf(TEXT("%d"), CurrentLV)));
		
		CurrentMaxHPNum->SetText(FText::FromString(FString::Printf(TEXT("%d"), CurrentMaxHP)));
		CurrentMaxStaminaNum->SetText(FText::FromString(FString::Printf(TEXT("%d"), CurrentMaxStamina)));

		CurrentVigorNum->SetText(FText::FromString(FString::Printf(TEXT("%d"), CurrentVigor)));
		CurrentEnduranceNum->SetText(FText::FromString(FString::Printf(TEXT("%d"), CurrentEndurance)));
		CurrentStrengthNum->SetText(FText::FromString(FString::Printf(TEXT("%d"), CurrentSTR)));
		CurrentVitalityNum->SetText(FText::FromString(FString::Printf(TEXT("%d"), CurrentVitality)));
		ChangeVigorNum->SetText(FText::FromString(FString::Printf(TEXT("%d"), tempChangeVigor)));
		ChangeEnduranceNum->SetText(FText::FromString(FString::Printf(TEXT("%d"), tempChangeEndurance)));
		ChangeStrengthNum->SetText(FText::FromString(FString::Printf(TEXT("%d"), tempChangeSTR)));
		ChangeVitalityNum->SetText(FText::FromString(FString::Printf(TEXT("%d"), tempChangeVitality)));

		CurrentDamageNum->SetText(FText::FromString(FString::Printf(TEXT("%d"), CurrentDamage)));
	}
}

void UGrowthWidget::pressDecisionbutton()
{
	auto Owner = GetWorld()->GetFirstPlayerController()->GetPawn();

	CurrentVigor = tempChangeVigor;
	CurrentEndurance = tempChangeEndurance;
	CurrentSTR = tempChangeSTR;
	CurrentVitality = tempChangeVitality;

	Cast<AAKP_ProjectCharacter>(Owner)->CharacterStat->SetVigor(CurrentVigor);
	Cast<AAKP_ProjectCharacter>(Owner)->CharacterStat->SetEndurance(CurrentEndurance);
	Cast<AAKP_ProjectCharacter>(Owner)->CharacterStat->SetStrength(CurrentSTR);
	Cast<AAKP_ProjectCharacter>(Owner)->CharacterStat->SetVitality(CurrentVitality);


	ReflashText();
}

