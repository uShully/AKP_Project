// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AKP_PROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	class AAKP_ProjectCharacter* Owner;

public:

	UInventoryComponent();

	virtual void BeginPlay() override;

	bool AddItem(class UItem* Item);
	bool RemoveItem(class UItem* Item);
	bool AddEquipItem(class UItem* Item, class UItem* EquipInventory);

	UPROPERTY(EditDefaultsOnly, Instanced)
		TArray<class UItem*> DefaultItems;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
		TArray<class UItem*> Items;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UItem* EquipRightHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UItem* EquipLeftHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UItem* EquipItem;
};
