// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterAnimIns.h"
#include "UObject/ConstructorHelpers.h"

UPlayerCharacterAnimIns::UPlayerCharacterAnimIns()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("AnimMontage'/Game/CharacterBP/PC_Attack_Montage.PC_Attack_Montage'"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DASHATTACK_MONTAGE(TEXT("AnimMontage'/Game/Animation/PlayerCharacterAnim/SwordAndShieldAttack_Montage.SwordAndShieldAttack_Montage'"));
	if (DASHATTACK_MONTAGE.Succeeded())
	{
		DashAttackMontage = DASHATTACK_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> BACKSTEP_MONTAGE(TEXT("AnimMontage'/Game/Animation/PlayerCharacterAnim/BackJump_Montage.BackJump_Montage'"));
	if (BACKSTEP_MONTAGE.Succeeded())
	{
		BackstepMontage = BACKSTEP_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ROLL_MONTAGE(TEXT("AnimMontage'/Game/Animation/PlayerCharacterAnim/mx_StandToRoll_Montage.mx_StandToRoll_Montage'"));
	if (ROLL_MONTAGE.Succeeded())
	{
		RollMontage = ROLL_MONTAGE.Object;
	}

}

void UPlayerCharacterAnimIns::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();	
	//return;
	//if (!IsDead)
		if (::IsValid(Pawn)) {
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character){
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}

void UPlayerCharacterAnimIns::PlayAttackMontage()
{	
	AKPCHECK(!IsDead);
	Montage_Play(AttackMontage, 1.f);
}

void UPlayerCharacterAnimIns::PlayDashAttackMontage()
{
	Montage_Play(DashAttackMontage, 1.f);
}

void UPlayerCharacterAnimIns::PlayBackstepMontage()
{
	if (!IsAnyMontagePlaying())
	Montage_Play(BackstepMontage, 1.f);
	
}

void UPlayerCharacterAnimIns::PlayRollMontage()
{
	if(!IsAnyMontagePlaying())
	Montage_Play(RollMontage, 1.f);
}

void UPlayerCharacterAnimIns::JumpToAttackMontageSection(int32 NewSection)
{
	AKPCHECK(!IsDead);
	AKPCHECK(Montage_IsPlaying(AttackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);

}

void UPlayerCharacterAnimIns::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}

void UPlayerCharacterAnimIns::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

FName UPlayerCharacterAnimIns::GetAttackMontageSectionName(int32 Section)
{
	AKPCHECK(FMath::IsWithinInclusive<int32>(Section, 1, 4), NAME_None);
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}