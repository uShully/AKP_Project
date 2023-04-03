// Fill out your copyright notice in the Description page of Project Settings.


#include "AKPGameInstance.h"
#include "AKPGameMode.h"
#include "PlayerStateWidget.h"

UAKPGameInstance::UAKPGameInstance()
{
	FString CharacterDataPath = TEXT("DataTable'/Game/DataTable/CharacterDataTable.CharacterDataTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_AKPCHARACTER(*CharacterDataPath);
	if(DT_AKPCHARACTER.Succeeded())
	AKPCharacterTable = DT_AKPCHARACTER.Object;

	FString CharacterStatDataPath = TEXT("DataTable'/Game/DataTable/CharacterStatDataTable.CharacterStatDataTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_AKPSTATINCREASE(*CharacterStatDataPath);
	if (DT_AKPSTATINCREASE.Succeeded())
		AKPStatIncreaseTable = DT_AKPSTATINCREASE.Object;
}

void UAKPGameInstance::Init()
{
	Super::Init(); 

}

FAKPCharacterData* UAKPGameInstance::GetAKPCharacterData(int32 Level)
{	
	return AKPCharacterTable->FindRow<FAKPCharacterData>(*FString::FromInt(Level), TEXT(""));
}

FAKPCharacterStatData* UAKPGameInstance::GetAKPStatIncreaseData(int32 value)
{
	return AKPStatIncreaseTable->FindRow<FAKPCharacterStatData>(*FString::FromInt(value), TEXT(""));
}

void UAKPGameInstance::AcquisitionOfBlood(int32 Blood)
{
	BloodOnHand += Blood;
	Cast<UPlayerStateWidget>(Cast<AAKPGameMode>(GetWorld()->GetAuthGameMode())->GetCurrentMainWidget())->RefreshBlood();
}

