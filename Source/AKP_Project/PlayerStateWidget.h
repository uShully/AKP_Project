// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AKP_Project.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStateWidget.generated.h"

/**
 * 
 */
UCLASS()
class AKP_PROJECT_API UPlayerStateWidget : public UUserWidget
{
	GENERATED_BODY()
	
		public:

	UFUNCTION()
		void RefreshBlood();

private:

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		int32 CurrentBlood;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
		class UTextBlock* BloodNum;
};
