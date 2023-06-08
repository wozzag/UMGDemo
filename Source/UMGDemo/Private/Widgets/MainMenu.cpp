#include "Widgets/MainMenu.h"
#include "Kismet/GameplayStatics.h"

UMainMenu::UMainMenu()
{
	//Constructor helpers to load textures 
	static ConstructorHelpers::FObjectFinder<UTexture2D> TXRMainMenuBGObj(TEXT("/Game/Textures/Widgets/TXRMainMenuBG"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> TXRMainMenuButtonObj(TEXT("/Game/Textures/Widgets/TXRMainMenuButton"));

	if (TXRMainMenuBGObj.Succeeded())
	{
		TXRMainMenuBG = TXRMainMenuBGObj.Object;
	}

	if (TXRMainMenuButtonObj.Succeeded())
	{
		TXRMainMenuButton = TXRMainMenuButtonObj.Object;
	}
}

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

	// Button styling
	FSlateBrush TextureBrush;
	FButtonStyle ButtonStyle;

	// Bind the function for which button was clicked/ hovered/ unhovered
	// Style the buttons
	for (int i = 0; i < MainMenuButtons.Num(); i++)
	{
		MainMenuButtons[i]->OnClickedDelegate.AddUniqueDynamic(this, &ThisClass::OnButtonWasClicked);
		MainMenuButtons[i]->OnHoveredDelegate.AddUniqueDynamic(this, &ThisClass::OnButtonWasHovered);
		MainMenuButtons[i]->UnHoveredDelegate.AddUniqueDynamic(this, &ThisClass::OnButtonWasUnHovered);
		MainMenuButtons[i]->TxtButton->SetText(FText::FromString(ButtonNames[i]));

		TextureBrush.SetResourceObject(TXRMainMenuButton);

		ButtonStyle.SetNormal(TextureBrush);
		ButtonStyle.SetHovered(TextureBrush);
		ButtonStyle.SetPressed(TextureBrush);

		ButtonStyle.Normal.OutlineSettings = 0.0f;
		ButtonStyle.Hovered.OutlineSettings = 0.0f;
		ButtonStyle.Pressed.OutlineSettings = 0.0f;

		MainMenuButtons[i]->CustomButton->SetStyle(ButtonStyle);
		MainMenuButtons[i]->CustomButton->SetStyle(ButtonStyle);
		MainMenuButtons[i]->CustomButton->SetStyle(ButtonStyle);

		MainMenuButtons[i]->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.7f));
	}

	// Set BG image
	ImgMainMenuBG->SetBrushFromTexture(TXRMainMenuBG);
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