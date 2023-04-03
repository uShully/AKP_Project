// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseCharacter.h"
#include "AKPAIController.h"
#include "CharacterStatComponent.h"
#include "Components/WidgetComponent.h"
#include "CharacterWidget.h"
#include "AKPGameInstance.h"
#include "DrawDebugHelpers.h"
#include "PlayerCharacterAnimIns.h" // 적 애님 변경시 삭제

// Sets default values
AEnemyBaseCharacter::AEnemyBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MESH(TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
	if (SK_MESH.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SK_MESH.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> CHARACTER_ANIM(TEXT("AnimBlueprint'/Game/CharacterBP/PlayerAnimBP.PlayerAnimBP_C'"));
	if (CHARACTER_ANIM.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(CHARACTER_ANIM.Class);
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -97.f), FRotator(0.f, 270.f, 0.f)); //XR YP ZY

	CharacterStat = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("CharacterStat"));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("AKPCharacter"));

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HPBarWidget->SetupAttachment(GetMesh());
	HPBarWidget->SetRelativeLocation(FVector(0.f, 0.f, 180.f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("WidgetBlueprint'/Game/UI/UI_HPBar.UI_HPBar_C'"));
	if (UI_HUD.Succeeded()) {
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.f, 50.f));
	}

	AIControllerClass = AAKPAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("AKPCharacter"));

	IsAttacking = false;

	MaxCombo = 4;
	AttackEndComboState();

	AttackRange = 200.f;
	AttackRadius = 50.f;
}

// Called when the game starts or when spawned
void AEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	BloodValue = 5000.f;
}

// Called every frame
void AEnemyBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CharAnim = Cast<UPlayerCharacterAnimIns>(GetMesh()->GetAnimInstance());
	AKPCHECK(nullptr != CharAnim);

	CharAnim->OnMontageEnded.AddDynamic(this, &AEnemyBaseCharacter::OnAttackMontageEnded);

	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {

		CharAnim->SetDeadAnim();
		SetActorEnableCollision(false);
		Cast<UAKPGameInstance>(GetWorld()->GetGameInstance())->AcquisitionOfBlood(BloodValue);
		});


	HPBarWidget->InitWidget();
	auto CharacterWidget = Cast<UCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	if (nullptr != CharacterWidget) {
		CharacterWidget->BindCharacterStat(CharacterStat);
	}
	else
	{
		AKPLOG(Warning, TEXT(" nullptr == CharacterWidget"));
	}

}

float AEnemyBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	AKPLOG(Warning, TEXT("Actor : %s took Damage : %f"), *GetName(), FinalDamage);

	if (FinalDamage > 0.f) {


		CharacterStat->SetDamage(FinalDamage);
	}

	return FinalDamage;
}

void AEnemyBaseCharacter::Attack()
{
	if (IsAttacking) {
		AKPCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if (CanNextCombo) {
			IsComboInputOn = true;
		}
	}
	else {
		AKPCHECK(CurrentCombo == 0);
		AttackStartComboState();
		CharAnim->PlayAttackMontage();
		CharAnim->JumpToAttackMontageSection(CurrentCombo);
		IsAttacking = true;

	}
}

void AEnemyBaseCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	AKPCHECK(IsAttacking);
	AKPCHECK(CurrentCombo > 0);
	IsAttacking = false;
	AttackEndComboState();
	OnAttackEnd.Broadcast();
}

void AEnemyBaseCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	AKPCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void AEnemyBaseCharacter::AttackEndComboState()
{
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}

void AEnemyBaseCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 200.f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
	);

#if ENABLE_DRAW_DEBUG

	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);

#endif

	if (bResult) {
		if (HitResult.Actor.IsValid()) {
			AKPLOG(Warning, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());

			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(CharacterStat->GetAttack(), DamageEvent, GetController(), this);

		}
	}
}