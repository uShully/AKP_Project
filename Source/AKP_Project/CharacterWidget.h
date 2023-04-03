// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AKP_Project.h"
#include "Blueprint/UserWidget.h"
#include "CharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class AKP_PROJECT_API UCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class UCharacterStatComponent* NewCharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdataHpWdiget();

private:
	TWeakObjectPtr<class UCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
		class UProgressBar* HPProgressBar;
};
