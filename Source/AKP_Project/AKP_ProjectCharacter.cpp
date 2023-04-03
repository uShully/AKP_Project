// Copyright Epic Games, Inc. All Rights Reserved.

#include "AKP_ProjectCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacterAnimIns.h"
#include "DrawDebugHelpers.h"
#include "AKPWeapon.h"
#include "CharacterStatComponent.h"
#include "Components/WidgetComponent.h"
#include "CharacterWidget.h"
#include "interactiveObject.h"
#include "InventoryComponent.h"
#include "Item.h"
#include "AKPAIController.h" // юс╫ц


//////////////////////////////////////////////////////////////////////////
// AAKP_ProjectCharacter

AAKP_ProjectCharacter::AAKP_ProjectCharacter()
{

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); 
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; 
	CameraBoom->bUsePawnControlRotation = true;


	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; 

	CharacterStat = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("CharacterStat"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MESH(TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
	if (SK_MESH.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SK_MESH.Object);
		}

	static ConstructorHelpers::FClassFinder<UAnimInstance> CHARACTER_ANIM(TEXT("AnimBlueprint'/Game/CharacterBP/PlayerAnimBP.PlayerAnimBP_C'"));
	if (CHARACTER_ANIM.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(CHARACTER_ANIM.Class);
	}

	IsAttacking = false;

	MaxCombo = 4;
	AttackEndComboState();

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("AKPCharacter"));

	AttackRange = 200.f;
	AttackRadius = 50.f;

	HealthPoint = 100.f;
	StaminaPoint = 100.f;

	/*
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HPBarWidget->SetupAttachment(GetMesh());
	HPBarWidget->SetRelativeLocation(FVector(0.f, 0.f, 180.f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("WidgetBlueprint'/Game/UI/UI_HPBar.UI_HPBar_C'"));
	if (UI_HUD.Succeeded()) {
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.f, 50.f));
	}
	*/
	CurrentInterActiveActor = nullptr;

	PrimaryActorTick.bCanEverTick = true;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAKP_ProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Running", IE_Pressed, this, &AAKP_ProjectCharacter::SetRunning);
	PlayerInputComponent->BindAction("Running", IE_Released, this, &AAKP_ProjectCharacter::SetRunning);
	PlayerInputComponent->BindAction("Roll", IE_Released, this, &AAKP_ProjectCharacter::Rolling);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AAKP_ProjectCharacter::SetCrouch);

	PlayerInputComponent->BindAction("SlowWalking", IE_Pressed, this, &AAKP_ProjectCharacter::SetSlowWalking);
	PlayerInputComponent->BindAction("SlowWalking", IE_Released, this, &AAKP_ProjectCharacter::SetSlowWalking);
	
	PlayerInputComponent->BindAction("Backstep", IE_Pressed, this, &AAKP_ProjectCharacter::Backstep);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AAKP_ProjectCharacter::Attack);
	PlayerInputComponent->BindAction("InterActive", IE_Pressed, this, &AAKP_ProjectCharacter::InteractToObject);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAKP_ProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAKP_ProjectCharacter::MoveRight);


	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AAKP_ProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AAKP_ProjectCharacter::LookUpAtRate);
}

void AAKP_ProjectCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AAKP_ProjectCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AAKP_ProjectCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AAKP_ProjectCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

//

void AAKP_ProjectCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	FName WeaponSocket(TEXT("hand_rSocket"));
	auto CurWeapon = GetWorld()->SpawnActor<AAKPWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (nullptr != CurWeapon) {
		CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
	}



}

void AAKP_ProjectCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	AKPLOG_S(Warning);
}

void AAKP_ProjectCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CharAnim = Cast<UPlayerCharacterAnimIns>(GetMesh()->GetAnimInstance());
	AKPCHECK(nullptr != CharAnim);


	CharAnim->OnMontageEnded.AddDynamic(this, &AAKP_ProjectCharacter::OnAttackMontageEnded);
	
	CharAnim->OnNextAttackCheck.AddLambda([this]() -> void {
			AKPLOG(Warning, TEXT("OnNextAttackCheck"));
			CanNextCombo = false;
			if (IsComboInputOn) {
				AttackStartComboState();
				CharAnim->JumpToAttackMontageSection(CurrentCombo);
			}
		}
	);

	CharAnim->OnAttackHitCheck.AddUObject(this, &AAKP_ProjectCharacter::AttackCheck);

	
	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {

		CharAnim->SetDeadAnim();
		SetActorEnableCollision(false);
	});


	/*
	HPBarWidget->InitWidget();
	auto CharacterWidget = Cast<UCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	if (nullptr != CharacterWidget) {
		CharacterWidget->BindCharacterStat(CharacterStat);
	}
	else
	{
		AKPLOG(Warning, TEXT(" nullptr == CharacterWidget"));
	}
	*/
}

void AAKP_ProjectCharacter::PossessedBy(AController* NewController)
{
	AKPLOG_S(Warning);
	Super::PossessedBy(NewController);


}

float AAKP_ProjectCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	AKPLOG(Warning, TEXT("Actor : %s took Damage : %f"), *GetName(), FinalDamage);

	if (FinalDamage > 0.f) {

	
		CharacterStat->SetDamage(FinalDamage);
	}

	return FinalDamage;
}

void AAKP_ProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsRunning && (GetVelocity().Size() < 1200.f || GetVelocity().Size() == 0.f) && !CharAnim->IsAnyMontagePlaying()) {		
		GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(GetCharacterMovement()->MaxWalkSpeed, MaxRunningSpeed + 5.f , DeltaTime, 1.f);
		AKPLOG(Warning, TEXT("Speed to running : %f"), GetVelocity().Size());
	}
	else if (!bIsRunning && (GetVelocity().Size() > 600.f || GetVelocity().Size() == 0.f) && !CharAnim->IsAnyMontagePlaying()) {
		GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(GetCharacterMovement()->MaxWalkSpeed, MaxWalkSpeed - 5.f, DeltaTime, 1.f);
		AKPLOG(Warning, TEXT("Speed to walk : %f"), GetVelocity().Size());
	}

}

void AAKP_ProjectCharacter::SetCrouch()
{
	if (!bIsCrouched) {
		Crouch();
		AKPLOG(Log, TEXT("Crouch"));
	}
	else {
		UnCrouch();
		AKPLOG(Log, TEXT("UnCrouch"));
	}
}

void AAKP_ProjectCharacter::SetRunning()
{
	if (CanRunning()) {
		bIsRunning = true;		
		//GetCharacterMovement()->MaxWalkSpeed = 1200.f;
	}
	else {
		bIsRunning = false;
		//GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}

}

bool AAKP_ProjectCharacter::CanRunning() const
{
	return !bIsRunning && !bIsSlowWalking && !bIsCrouched && GetRootComponent() && !GetRootComponent()->IsSimulatingPhysics();
}

void AAKP_ProjectCharacter::SetSlowWalking()
{
	if (CanSlowWaling()) {
		bIsSlowWalking = true;
		GetCharacterMovement()->MaxWalkSpeed = 100.f;
		AKPLOG(Log, TEXT("Start slow walk"));
	}
	else {
		bIsSlowWalking = false;
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
		AKPLOG(Log, TEXT("stop slow walk"));
	}
}

bool AAKP_ProjectCharacter::CanSlowWaling() const
{
	return !bIsRunning && !bIsSlowWalking && !bIsCrouched && GetRootComponent() && !GetRootComponent()->IsSimulatingPhysics();
}

void AAKP_ProjectCharacter::Backstep()
{
	if(GetVelocity().Size() <= 0.f ) {
		CharAnim->PlayBackstepMontage();

		// find out which way is right
		/*
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction

		float DashDistance = 1000.f;
		const FVector ForwardDir = GetActorRotation().Vector();

		LaunchCharacter(ForwardDir * DashDistance * FVector(-1.f, -1.f, 0.f) , true, true);
		AKPLOG(Log, TEXT("%s"), *ForwardDir.ToString());
		*/
	}
}

void AAKP_ProjectCharacter::Rolling()
{
	if (GetVelocity().Size() <= 900.f && GetVelocity().Size() > 10.f && bIsRunning == false) {
		CharAnim->PlayRollMontage();	
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}
}

void AAKP_ProjectCharacter::Attack()
{
	if (IsAttacking) {
		AKPCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if (CanNextCombo) {
			IsComboInputOn = true;
		}
	}
	else {
		AKPCHECK(CurrentCombo == 0);
		if(GetVelocity().Size() <= 600) {
			AttackStartComboState();
			CharAnim->PlayAttackMontage();
			CharAnim->JumpToAttackMontageSection(CurrentCombo);
			IsAttacking = true;
		}
		else {
			CharAnim->PlayDashAttackMontage();
		}

	
	}
}

void AAKP_ProjectCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	AKPCHECK(IsAttacking);
	AKPCHECK(CurrentCombo > 0);
	IsAttacking = false;
	AttackEndComboState();
}

void AAKP_ProjectCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	AKPCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void AAKP_ProjectCharacter::AttackEndComboState()
{
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}

void AAKP_ProjectCharacter::AttackCheck()
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

void AAKP_ProjectCharacter::InteractToObject()
{
	if (nullptr != CurrentInterActiveActor) {
		AKPLOG(Warning, TEXT(" Interactive actor name : %s" ), *CurrentInterActiveActor->GetName());
		Cast<AInteractiveObject>(CurrentInterActiveActor)->InteractPure();
	}
	else {
		AKPLOG(Warning, TEXT(" Interactive actor name : nullptr"));
	}
}

void AAKP_ProjectCharacter::Interact_Implementation()
{
	AKPLOG(Warning, TEXT("Implementation"));
}

void AAKP_ProjectCharacter::InteractPure()
{
	AKPLOG(Warning, TEXT("pure"));
}

void AAKP_ProjectCharacter::UseItem(UItem* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->OnUse(this);

	}
}