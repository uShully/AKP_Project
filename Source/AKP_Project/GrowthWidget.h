// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GrowthWidget.generated.h"

/**
 * 
 */
UCLASS()
class AKP_PROJECT_API UGrowthWidget : public UUserWidget
{
	GENERATED_BODY()

		virtual void NativeConstruct() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		class UTextBlock* LevelNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		class UTextBlock* CurrentMaxHPNum;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		class UTextBlock* CurrentMaxStaminaNum;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		class UTextBlock* CurrentVigorNum;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		class UTextBlock* ChangeVigorNum;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		class UTextBlock* CurrentEnduranceNum;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		class UTextBlock* ChangeEnduranceNum;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		class UTextBlock* CurrentStrengthNum;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		class UTextBlock* ChangeStrengthNum;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		class UTextBlock* CurrentVitalityNum;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		class UTextBlock* ChangeVitalityNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		class UTextBlock* CurrentDamageNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		int32 CurrentLV;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		int32 CurrentMaxHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		int32 CurrentMaxStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		int32 CurrentVigor;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		int32 tempChangeVigor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		int32 CurrentEndurance;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		int32 tempChangeEndurance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		int32 CurrentSTR;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		int32 tempChangeSTR;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		int32 CurrentVitality;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		int32 tempChangeVitality;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		int32 CurrentDamage;

	void ReflashText();

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
		void pressDecisionbutton();
};
