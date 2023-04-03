// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWidget.h"
#include "CharacterStatComponent.h"
#include "Components/ProgressBar.h"

void UCharacterWidget::BindCharacterStat(UCharacterStatComponent* NewCharacterStat)
{
	AKPCHECK(nullptr != NewCharacterStat);

	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChanged.AddUObject(this, &UCharacterWidget::UpdataHpWdiget);
}

void UCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	AKPCHECK(nullptr != HPProgressBar);
	UpdataHpWdiget();
}

void UCharacterWidget::UpdataHpWdiget()
{
	if (CurrentCharacterStat.IsValid()) {
		if (nullptr != HPProgressBar) {
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}
}
