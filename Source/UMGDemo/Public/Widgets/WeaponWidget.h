// Widget for the weapon data

#pragma once

#include "CoreMinimal.h"
#include "WidgetsBase.h"
#include "MovieScene.h"
#include "Animation/WidgetAnimation.h"
#include "WeaponWidget.generated.h"

// Forward declaration
class UTextBlock;
class UImage;

UCLASS()
class UMGDEMO_API UWeaponWidget : public UWidgetsBase
{
	GENERATED_BODY()

public:

	// Bound widgets and animation 
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* AnimWeaponWidget;

	UPROPERTY(meta = (BindWidget))
	UImage* ImgWeapon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TxtCurrentAmmo;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TxtMaxAmmo;

	// Play animation
	bool PlayAnimationByName(FName AnimationName,
		float StartAtTime,
		int32 NumLoopsToPlay,
		EUMGSequencePlayMode::Type PlayMode,
		float PlaybackSpeed);

protected:

	virtual void NativeConstruct() override;

	// Get animation
	UWidgetAnimation* GetAnimationByName(FName AnimationName) const;
	
protected:

	// Map for animations
	TMap<FName, UWidgetAnimation*> AnimationsMap;

	void FillAnimationsMap();
};
