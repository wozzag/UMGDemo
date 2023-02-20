// This class controls the UMG widgets and textures 
// Calls other classes and sets their UMG data based on events in the game
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Widgets/InGameHUD.h"
#include "Widgets/MainMenu.h"
#include "Weapons/WeaponBase.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UMGDemoPlayerController.generated.h"

UCLASS()
class UMGDEMO_API AUMGDemoPlayerController : public APlayerController
{
	GENERATED_BODY()

	AUMGDemoPlayerController();
	
public:

// Textures

	// MainMenu 
	UPROPERTY()
	UTexture2D* TXRMainMenuBG;

	UPROPERTY()
	UTexture2D* TXRMainMenuButton;

	// InGameHud
	UPROPERTY()
	UTexture2D* TXRDistance;

	UPROPERTY()
	UTexture2D* TXRMap;

	// ProgressBars
	UPROPERTY()
	UTexture2D* TXRPBLine;

//Widgets

	// Main menu widget class and instance
	UPROPERTY()
	TSubclassOf<UMainMenu> MainMenuClass;

	UPROPERTY()
	UMainMenu* MainMenuInstance;

	// PlayerHUD widget class and instance
	UPROPERTY()
	TSubclassOf<UInGameHUD> InGameHUDClass;

	UPROPERTY()
	UInGameHUD* InGameHUDInstance;

public:
	virtual void BeginPlay() override;

	// Create widgets and set data
	void CreateMainMenuWidget();

	void CreateInGameWidget();

	void SetMainMenuData();

	void SetInGameData();

	// Show the weapon widgets when the player overlaps the weapons
	// Called from Player Character "AddWeapon" function using delegate in AWeaponBase
	void ShowWeaponWidgets(int32 WeaponCount, AWeaponBase* Weapon);

	// Timerhandler and function
	FTimerHandle InfoBarTimerHandle;

	UFUNCTION()
	void SetInfoBarData();
};
