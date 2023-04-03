// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AKP_Project.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "AKPGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FAKPCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FAKPCharacterData() : Level(1), MaxHP(500.f), MaxStamina(100.f), Vigor(10), Endurance(10), Strength(10), Vitality(10) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Level; // 레벨은 폐기 예정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Vigor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Endurance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Strength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Vitality;
}; // 초기 캐릭터 능력치 데이터 테이블

USTRUCT(BlueprintType)
struct FAKPCharacterStatData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float VigorIncreaseValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float EnduranceIncreaseValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float StrengthIncreaseValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float VitalityIncreaseValue;
};
/**
 * 
 */
UCLASS()
class AKP_PROJECT_API UAKPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UAKPGameInstance();
		
		virtual void Init() override;
		FAKPCharacterData* GetAKPCharacterData(int32 Level);
		FAKPCharacterStatData* GetAKPStatIncreaseData(int32 value);
private:
	UPROPERTY()
		class UDataTable* AKPCharacterTable;
	UPROPERTY()
		class UDataTable* AKPStatIncreaseTable;
	

	UPROPERTY()
		int32 BloodOnHand = 0;

public:
	UFUNCTION()
		void AcquisitionOfBlood(int32 Blood);

	UFUNCTION()
		int32 GetBlood() { return BloodOnHand; };

};
