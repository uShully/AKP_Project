// Fill out your copyright notice in the Description page of Project Settings.


#include "AKPGameMode.h"
#include "AKP_ProjectCharacter.h"
#include "AKPPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

AAKPGameMode::AAKPGameMode()
{
	DefaultPawnClass = AAKP_ProjectCharacter::StaticClass();
	PlayerControllerClass = AAKPPlayerController::StaticClass();
	
	static ConstructorHelpers::FClassFinder<AAKP_ProjectCharacter> BP_Character_C(TEXT("Blueprint'/Game/CharacterBP/ThirdPersonCharacter.ThirdPersonCharacter_C'"));
	if (BP_Character_C.Succeeded())
	{
		DefaultPawnClass = BP_Character_C.Class;
	}

	
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_PLAYERSTATE(TEXT("WidgetBlueprint'/Game/UI/UI_PlayerStateBar.UI_PlayerStateBar_C'"));
	if (UI_PLAYERSTATE.Succeeded())
	{
		PlayerStateWidgetClass = UI_PLAYERSTATE.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_INTERACTIVEUI(TEXT("WidgetBlueprint'/Game/UI/UI_InteractiveItem.UI_InteractiveItem_C'"));
	if (UI_INTERACTIVEUI.Succeeded())
	{
		InterActiveWidgetClass = UI_INTERACTIVEUI.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_NPCINTERACTIVEUI(TEXT("WidgetBlueprint'/Game/UI/UI_NPCInteractiveWidget.UI_NPCInteractiveWidget_C'"));
	if (UI_NPCINTERACTIVEUI.Succeeded())
	{
		NPCInterActiveWidgetClass = UI_NPCINTERACTIVEUI.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_BONFIREINTERACTIVEUI(TEXT("WidgetBlueprint'/Game/UI/UI_BonfireInteractiveWidget.UI_BonfireInteractiveWidget_C'"));
	if (UI_BONFIREINTERACTIVEUI.Succeeded())
	{
		BonfireInterActiveWidgetClass = UI_BONFIREINTERACTIVEUI.Class;
	}
}

void AAKPGameMode::PostLogin(APlayerController* NewPlayer)
{
	AKPLOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	AKPLOG(Warning, TEXT("PostLogin End"));

	
	
}

void AAKPGameMode::BeginPlay()
{
	Super::BeginPlay();

	ChangeMainWidget(PlayerStateWidgetClass);
}

void AAKPGameMode::ChangeMainWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	//RemoveWidgetFromViewPort();

	if (nullptr != NewWidgetClass) {
		CurrentMainWidget = CreateWidget(GetWorld(), NewWidgetClass);
		if (nullptr != CurrentMainWidget) {
			CurrentMainWidget->AddToViewport();
		}
	}
}

void AAKPGameMode::ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	
	RemoveWidgetFromViewPort();

	if (nullptr != NewWidgetClass) {
		
		CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass);
		if (nullptr != CurrentWidget) {
			CurrentWidget->AddToViewport();
		}
	}
}

void AAKPGameMode::RemoveWidgetFromViewPort()
{
	if (nullptr != CurrentWidget) {
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
}

void AAKPGameMode::AddToViewInterActiveWidget()
{
	ChangeWidget(InterActiveWidgetClass);
}

void AAKPGameMode::AddToViewNPCInterActiveWidget()
{
	ChangeWidget(NPCInterActiveWidgetClass);
}

void AAKPGameMode::AddToViewBonfireInterActiveWidget()
{
	ChangeWidget(BonfireInterActiveWidgetClass);
}

void AAKPGameMode::SetControllerwhileUIActive(bool bActive)
{
	if (bActive) {
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(bActive);
	}
	else {
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(bActive);
	}
}
