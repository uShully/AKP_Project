// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AKP_Project.h"
#include "GameFramework/GameModeBase.h"
#include "AKPGameMode.generated.h"

/**
 * 
 */
UCLASS()
class AKP_PROJECT_API AAKPGameMode : public AGameModeBase
{
	GENERATED_BODY()

		AAKPGameMode();

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	UFUNCTION(BlueprintCallable, Category = "UMG_Game")
		void ChangeMainWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	UFUNCTION(BlueprintCallable, Category = "UMG_Game")
		void ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UFUNCTION()
		UUserWidget* GetCurrentMainWidget() { return CurrentMainWidget; };

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> PlayerStateWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> InterActiveWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> NPCInterActiveWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> BonfireInterActiveWidgetClass;

	UPROPERTY()
		UUserWidget* CurrentMainWidget;
	UPROPERTY()
		UUserWidget* CurrentWidget;

public:

	UFUNCTION()
		void RemoveWidgetFromViewPort();

	UFUNCTION()
		void AddToViewInterActiveWidget();

	UFUNCTION()
		void AddToViewNPCInterActiveWidget();

	UFUNCTION()
		void AddToViewBonfireInterActiveWidget();

	UFUNCTION(BlueprintCallable, Category = "UMG_Game")
	void SetControllerwhileUIActive(bool bActive);
	
};
