// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateWidget.h"
#include "Components/TextBlock.h"
#include "AKPGameInstance.h"

void UPlayerStateWidget::NativeConstruct()
{
	Super::NativeConstruct();	

	RefreshBlood();
}

void UPlayerStateWidget::RefreshBlood()
{
	CurrentBlood = Cast<UAKPGameInstance>(GetWorld()->GetGameInstance())->GetBlood();
	BloodNum->SetText(FText::FromString(FString::Printf(TEXT("%d"), CurrentBlood)));
}