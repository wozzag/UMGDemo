#include "Widgets/MainMenu.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	// Add bound buttons to an array
	MainMenuButtons.Add(BtnPlay);
	MainMenuButtons.Add(BtnNewGame);
	MainMenuButtons.Add(BtnLoadGame);
	MainMenuButtons.Add(BtnOptions);
	MainMenuButtons.Add(BtnCredits);

	// Text for the buttons
	ButtonNames.Add("Play");
	ButtonNames.Add("New Game");
	ButtonNames.Add("Load Game");
	ButtonNames.Add("Options");
	ButtonNames.Add("Credits");

	// Bind the function for which button was clicked/ hovered/ unhovered
	for (int i = 0; i < MainMenuButtons.Num(); i++)
	{
		MainMenuButtons[i]->OnClickedDelegate.AddUniqueDynamic(this, &ThisClass::OnButtonWasClicked);
		MainMenuButtons[i]->OnHoveredDelegate.AddUniqueDynamic(this, &ThisClass::OnButtonWasHovered);
		MainMenuButtons[i]->UnHoveredDelegate.AddUniqueDynamic(this, &ThisClass::OnButtonWasUnHovered);
	}
}

// Get the button by name and open the level
void UMainMenu::OnButtonWasClicked(UCustomButton* Button)
{
	if (Button->GetName() == "BtnPlay")
	{
		UGameplayStatics::OpenLevel(this, "lvlInGame");
	}
}

// Highlight selected button/ dim the others
void UMainMenu::OnButtonWasHovered(UCustomButton* Button)
{
	Button->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
}

void UMainMenu::OnButtonWasUnHovered(UCustomButton* Button)
{
	for (int i = 0; i < MainMenuButtons.Num(); i++)
	{
		MainMenuButtons[i]->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.7f));
	}
}