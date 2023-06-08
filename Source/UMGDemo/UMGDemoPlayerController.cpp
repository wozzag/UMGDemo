#include "UMGDemoPlayerController.h"

AUMGDemoPlayerController::AUMGDemoPlayerController()
{
	static ConstructorHelpers::FClassFinder<UMainMenu> WBP_MainMenuClass(TEXT("/Game/Widgets/WBP_MainMenu"));
	static ConstructorHelpers::FClassFinder<UInGameHUD> WBP_InGameHUDClass(TEXT("/Game/Widgets/WBP_InGameHUD"));

	// Widgets
	if (WBP_MainMenuClass.Succeeded()) 
	{
		MainMenuClass = WBP_MainMenuClass.Class;
	}

	if (WBP_InGameHUDClass.Succeeded()) 
	{
		InGameHUDClass = WBP_InGameHUDClass.Class;
	}
 }

void AUMGDemoPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	// Get pure level name
	FString CurrentLevelName = GetWorld()->GetMapName();
	CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	// Create the widgets
	if (CurrentLevelName == "lvlMainMenu")
	{
		if (MainMenuClass)
		{
			CreateMainMenuWidget();
		}
	}
	else
	{
		if (InGameHUDClass)
		{
			CreateInGameWidget();
		}
	}
}

// Main menu
void AUMGDemoPlayerController::CreateMainMenuWidget()
{
	MainMenuInstance = CreateWidget<UMainMenu>(this, MainMenuClass);
	MainMenuInstance->AddToViewport();
}

// InGameHUD
void AUMGDemoPlayerController::CreateInGameWidget()
{
	InGameHUDInstance = CreateWidget<UInGameHUD>(this, InGameHUDClass);
	InGameHUDInstance->AddToViewport();
}