// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "HealingItem.generated.h"

/**
 * 
 */
UCLASS()
class AKP_PROJECT_API UHealingItem : public UItem
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
		float HealthToHeal;

protected:


	virtual void Use(class AAKP_ProjectCharacter* Character) override;
};
