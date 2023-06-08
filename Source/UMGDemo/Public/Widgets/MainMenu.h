// Main menu widget

#pragma once

#include "CoreMinimal.h"
#include "WidgetsBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Widgets/CustomButton.h"
#include "MainMenu.generated.h"

UCLASS()
class UMGDEMO_API UMainMenu : public UWidgetsBase
{
	GENERATED_BODY()

	UMainMenu();

public:

	// Bind our buttons in this widget
	UPROPERTY(meta = (BindWidget))
	UCustomButton* BtnPlay;

	UPROPERTY(meta = (BindWidget))
	UCustomButton* BtnNewGame;

	UPROPERTY(meta = (BindWidget))
	UCustomButton* BtnLoadGame;

	UPROPERTY(meta = (BindWidget))
	UCustomButton* BtnOptions;

	UPROPERTY(meta = (BindWidget))
	UCustomButton* BtnCredits;

	// Array of bound buttons
	TArray<UCustomButton*> MainMenuButtons;

	// Array of button names
	TArray<FString> ButtonNames;

	// Images for this widget
	UPROPERTY(meta = (BindWidget))
	UImage* ImgMainMenuBG;

	// Textures
	UPROPERTY()
	UTexture2D* TXRMainMenuBG;

	UPROPERTY()
	UTexture2D* TXRMainMenuButton;

protected:

	virtual void NativeConstruct() override;

	// Functions that returns which button was clicked/ hovered/ unhovered
	UFUNCTION()
	void OnButtonWasClicked(UCustomButton* Button);

	UFUNCTION()
	void OnButtonWasHovered(UCustomButton* Button);

	UFUNCTION()
	void OnButtonWasUnHovered(UCustomButton* Button);
};
