// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AKP_Project.h"
#include "GameFramework/Character.h"
#include "InterActiveInterface.h"
#include "AKP_ProjectCharacter.generated.h"

UCLASS(config=Game)
class AAKP_ProjectCharacter : public ACharacter, public IInterActiveInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;


	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Tick(float DeltaTime) override;

public:
	
	UPROPERTY(VisibleAnywhere, Category = Weapon)
		USkeletalMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
		class UCharacterStatComponent* CharacterStat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
		class UInventoryComponent* Inventory;

public:
	AAKP_ProjectCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* HPBarWidget;


protected:



	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);



protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:

	UPROPERTY(EditAnywhere, Category = "Character_State" , Meta = (AllowPrivateAccess = true))
		float HealthPoint = 0.f;

	UPROPERTY(EditAnywhere, Category = "Character_State", Meta = (AllowPrivateAccess = true))
		float StaminaPoint = 0.f;

	UPROPERTY(EditAnywhere, Category = "Character_State", Meta = (AllowPrivateAccess = true))
		float MaxWalkSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category = "Character_State", Meta = (AllowPrivateAccess = true))
		float MaxRunningSpeed = 1200.f;

	UFUNCTION()
		void SetCrouch();

	UFUNCTION()
		void SetRunning();

	bool bIsRunning = false;

	UFUNCTION()
		void SetSlowWalking();

	bool bIsSlowWalking = false;
	
	bool CanRunning() const;
	bool CanSlowWaling() const;

	UFUNCTION()
		void Backstep();

	void Rolling();
	
	void Attack();

	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();


private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool CanNextCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsComboInputOn;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		int32 MaxCombo;

	UPROPERTY()
		class UPlayerCharacterAnimIns* CharAnim;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRadius;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		AActor* CurrentInterActiveActor;

	void InteractToObject();
public:

	void SetCurrentInterActiveActor(AActor* InteractActor) { CurrentInterActiveActor = InteractActor; };

	void Interact_Implementation() override;
	virtual void InteractPure() override;

	UFUNCTION(BlueprintCallable, Category = "Items")
		void UseItem(class UItem* Item);


};

