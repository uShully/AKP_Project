// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Item.h"
#include "AKP_ProjectCharacter.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = Cast<AAKP_ProjectCharacter>(GetOwner());

	

	AddEquipItem(DefaultItems[0]);
	AddEquipRightHandItem(DefaultItems[1]);
	AddEquipLeftHandItem(DefaultItems[2]);

}

bool UInventoryComponent::AddEquipItem(class UItem* Item, class UItem* EquipInventory)
{
	Item->OwingInventory = this;
	Item->World = GetWorld();
	EquipInventory = Item;

	OnInventoryUpdated.Broadcast();

	return true;
}

bool UInventoryComponent::AddEquipItem(UItem* Item)
{
	Item->OwingInventory = this;
	Item->World = GetWorld();
	EquipItem = Item;

	OnInventoryEquipItemUpdated.Broadcast();

	return true;
}

bool UInventoryComponent::AddEquipRightHandItem(UItem* Item)
{
	Item->OwingInventory = this;
	Item->World = GetWorld();
	EquipRightHand = Item;

	OnInventoryEquipRightHandUpdated.Broadcast();

	return true;
}

bool UInventoryComponent::AddEquipLeftHandItem(UItem* Item)
{
	Item->OwingInventory = this;
	Item->World = GetWorld();
	EquipLeftHand = Item;

	OnInventoryEquipLeftHandUpdated.Broadcast();

	return true;
}


bool UInventoryComponent::AddItem(class UItem* Item)
{
	Item->OwingInventory = this;
	Item->World = GetWorld();
	Items.Add(Item);

	
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UInventoryComponent::RemoveItem(class UItem* Item)
{
	if (Item)
	{
		Item->OwingInventory = nullptr;
		Item->World = nullptr;
		Items.RemoveSingle(Item);
		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}

