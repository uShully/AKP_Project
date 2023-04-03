// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AKP_Project.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class AKP_PROJECT_API UItem : public UObject
{
	GENERATED_BODY()
	
public:

	UItem();

	virtual class UWorld* GetWorld() const { return World; };

	UPROPERTY(Transient)
		class UWorld* World;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		class UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText ItemDisplayName;

	UPROPERTY()
		class UInventoryComponent* OwingInventory;

	virtual void Use(class AAKP_ProjectCharacter* Character) PURE_VIRTUAL(UItem, );

	UFUNCTION(BlueprintImplementableEvent)
		void OnUse(class AAKP_ProjectCharacter* Character);
};
