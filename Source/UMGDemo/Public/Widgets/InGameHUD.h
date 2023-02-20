// InGame class
#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetsBase.h"
#include "Widgets/WeaponWidget.h"
#include "Widgets/InfoProgressBar.h"
#include "InGameHUD.generated.h"

// Forward declarations
class UImage;
class UProgressBar;
class UTextBlock;

UCLASS()
class UMGDEMO_API UInGameHUD : public UWidgetsBase
{
	GENERATED_BODY()

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

protected:

	virtual void NativeConstruct() override;

};
