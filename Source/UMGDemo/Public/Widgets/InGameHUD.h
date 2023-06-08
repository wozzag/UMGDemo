// InGame class
#pragma once

#include "CoreMinimal.h"
#include "WidgetsBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Widgets/WeaponWidget.h"
#include "Widgets/InfoProgressBar.h"
#include "Weapons/WeaponBase.h"
#include "InGameHUD.generated.h"

UCLASS()
class UMGDEMO_API UInGameHUD : public UWidgetsBase
{
	GENERATED_BODY()

	UInGameHUD();

public:

	// Bound Weapon widget classes
	UPROPERTY(meta = (BindWidget))
	UWeaponWidget* WBP_WeaponPrimary;

	UPROPERTY(meta = (BindWidget))
	UWeaponWidget* WBP_WeaponSecondary;

	UPROPERTY(meta = (BindWidget))
	UWeaponWidget* WBP_WeaponTertiary;

	// Array of Weapon widget class
	TArray<UWeaponWidget*> WeaponWidgets;

	// Bound progress bars classes
	UPROPERTY(meta = (BindWidget))
	UInfoProgressBar* WBP_InfoProgressBarTop;

	UPROPERTY(meta = (BindWidget))

	UInfoProgressBar* WBP_InfoProgressBarMid;

	UPROPERTY(meta = (BindWidget))
	UInfoProgressBar* WBP_InfoProgressBarBtm;

	UPROPERTY(meta = (BindWidget))
	UInfoProgressBar* WBP_HealthProgressBar;

	// Array of progress bars class
	TArray<UInfoProgressBar*> InfoProgressBars;

	// Textblock / images
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TxtDistance;

	UPROPERTY(meta = (BindWidget))
	UImage* ImgMap;

	UPROPERTY(meta = (BindWidget))
	UImage* ImgDistance;

	// Textures
	UPROPERTY()
	UTexture2D* TXRDistance;

	UPROPERTY()
	UTexture2D* TXRMap;

	UPROPERTY()
	UTexture2D* TXRPBLine;

protected:

	virtual void NativeConstruct() override;

public:

	// Timerhandler and function for random progress bar percent
	FTimerHandle InfoBarTimerHandle;

	// Set the random percent of progress bar
	UFUNCTION()
	void SetInfoBarData();

	// Show the weapon widgets
	void ShowWeaponWidgets(int32 WeaponCount, AWeaponBase* Weapon);
};
