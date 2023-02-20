#include "UMGDemoPlayerController.h"

AUMGDemoPlayerController::AUMGDemoPlayerController()
{
	//Constructor helpers to load textures and widgets
	static ConstructorHelpers::FObjectFinder<UTexture2D> TXRMainMenuBGObj(TEXT("/Game/Textures/Widgets/TXRMainMenuBG"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> TXRMainMenuButtonObj(TEXT("/Game/Textures/Widgets/TXRMainMenuButton"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> TXRPBLineObj(TEXT("/Game/Textures/Widgets/TXRPBLine"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> TXRDistanceObj(TEXT("/Game/Textures/Widgets/TXRDistance"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> TXRMapObj(TEXT("/Game/Textures/Widgets/TXRMap"));

	static ConstructorHelpers::FClassFinder<UMainMenu> WBP_MainMenuClass(TEXT("/Game/Widgets/WBP_MainMenu"));
	static ConstructorHelpers::FClassFinder<UInGameHUD> WBP_InGameHUDClass(TEXT("/Game/Widgets/WBP_InGameHUD"));

	if (TXRMainMenuBGObj.Succeeded())
	{
		TXRMainMenuBG = TXRMainMenuBGObj.Object;
	}

	if (TXRMainMenuButtonObj.Succeeded())
	{
		TXRMainMenuButton = TXRMainMenuButtonObj.Object;
	}

	if (TXRPBLineObj.Succeeded())
	{
		TXRPBLine = TXRPBLineObj.Object;
	}
	
	if (TXRDistanceObj.Succeeded())
	{
		TXRDistance = TXRDistanceObj.Object;
	}

	if (TXRMapObj.Succeeded())
	{
		TXRMap = TXRMapObj.Object;
	}
	
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

	// Get pure level name
	FString CurrentLevelName = GetWorld()->GetMapName();
	CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	// Create the widget ans set data
	if (CurrentLevelName == "lvlMainMenu")
	{
		if (MainMenuClass)
		{
			CreateMainMenuWidget();
			SetMainMenuData();
		}
	}
	else
	{
		if (InGameHUDClass)
		{
			CreateInGameWidget();
			SetInGameData();
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

//  Main menu data/ set buttons textures / set background texture
void AUMGDemoPlayerController::SetMainMenuData()
{
	for (int i = 0; i < MainMenuInstance->MainMenuButtons.Num(); i++)
	{
		MainMenuInstance->MainMenuButtons[i]->TxtButton->SetText(FText::FromString(MainMenuInstance->ButtonNames[i]));

		MainMenuInstance->MainMenuButtons[i]->CustomButton->WidgetStyle.Normal.SetResourceObject(TXRMainMenuButton);
		MainMenuInstance->MainMenuButtons[i]->CustomButton->WidgetStyle.Hovered.SetResourceObject(TXRMainMenuButton);
		MainMenuInstance->MainMenuButtons[i]->CustomButton->WidgetStyle.Pressed.SetResourceObject(TXRMainMenuButton);

		MainMenuInstance->MainMenuButtons[i]->CustomButton->WidgetStyle.Normal.OutlineSettings.Width = 0.0f;
		MainMenuInstance->MainMenuButtons[i]->CustomButton->WidgetStyle.Hovered.OutlineSettings.Width = 0.0f;
		MainMenuInstance->MainMenuButtons[i]->CustomButton->WidgetStyle.Pressed.OutlineSettings.Width = 0.0f;

		MainMenuInstance->MainMenuButtons[i]->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.7f));
	}
	MainMenuInstance->ImgMainMenuBG->SetBrushFromTexture(TXRMainMenuBG);
}

// InGame data
void AUMGDemoPlayerController::SetInGameData()
{
	// Hide weapon widgets/ set textures/ text
	for (int i = 0; i < InGameHUDInstance->WeaponWidgets.Num(); i++)
	{
		InGameHUDInstance->WeaponWidgets[i]->SetVisibility(ESlateVisibility::Hidden);
	}

	InGameHUDInstance->ImgMap->SetBrushFromTexture(TXRMap);
	InGameHUDInstance->ImgDistance->SetBrushFromTexture(TXRDistance);

	FString DistanceString = "567";
	InGameHUDInstance->TxtDistance->SetText(FText::FromString(DistanceString));

	// Timerhandler for random progressbar percents
	GetWorld()->GetTimerManager().SetTimer(InfoBarTimerHandle, this, &AUMGDemoPlayerController::SetInfoBarData, 0.2f, true);

	// Set progress bars and health bar text/ texture / color / line / scale
	FLinearColor ProgressBarColor = FLinearColor(0.16f, 0.72f, 0.7f, 1.0f);

	for (int i = 0; i < InGameHUDInstance->InfoProgressBars.Num(); i++)
	{
		InGameHUDInstance->InfoProgressBars[i]->TxtInfo->SetText(FText::FromString(InGameHUDInstance->InfoProgressBars[i]->InfoBarNames[i]));
		InGameHUDInstance->InfoProgressBars[i]->ImgInfoLine->SetBrushFromTexture(TXRPBLine);
		InGameHUDInstance->InfoProgressBars[i]->ProgressBar->SetFillColorAndOpacity(ProgressBarColor);
	}

	FWidgetTransform ProgressBarTransform = InGameHUDInstance->WBP_HealthProgressBar->ProgressBar->GetRenderTransform();
	ProgressBarTransform.Scale.Y = 3.0f;

	InGameHUDInstance->WBP_HealthProgressBar->TxtInfo->SetText(FText::FromString("Health"));
	InGameHUDInstance->WBP_HealthProgressBar->ProgressBar->SetRenderTransform(ProgressBarTransform);
	InGameHUDInstance->WBP_HealthProgressBar->ProgressBar->SetFillColorAndOpacity(ProgressBarColor);
	InGameHUDInstance->WBP_HealthProgressBar->ImgInfoLine->SetBrushFromTexture(TXRPBLine);
}

// Set random value for info progress bars
void AUMGDemoPlayerController::SetInfoBarData()
{
	for (int i = 0; i < InGameHUDInstance->InfoProgressBars.Num(); i++)
	{
		float RandAmount = FMath::RandRange(0.0f, 1.0f);
		InGameHUDInstance->InfoProgressBars[i]->ProgressBar->SetPercent(RandAmount);
	}
}

// Show weapon widgets/ set opacity of other widgets/ play widget animation/ set the text 
void AUMGDemoPlayerController::ShowWeaponWidgets(int32 WeaponCount, AWeaponBase* Weapon)
{
	if (WeaponCount == 0)
	{
		InGameHUDInstance->WeaponWidgets[WeaponCount]->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		InGameHUDInstance->WeaponWidgets[WeaponCount]->SetVisibility(ESlateVisibility::Visible);
		InGameHUDInstance->WeaponWidgets[WeaponCount]->ImgWeapon->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.5f));
	}

	InGameHUDInstance->WeaponWidgets[WeaponCount]->PlayAnimationByName("AnimWeaponWidget",
		0.0f,
		1,
		EUMGSequencePlayMode::PingPong,
		1.0f);

	InGameHUDInstance->WeaponWidgets[WeaponCount]->ImgWeapon->SetBrushFromTexture(Weapon->WeaponStruct.WeaponTexture);

	FText AmmoText = FText::AsNumber(Weapon->WeaponStruct.GetCurrentAmmo());
	InGameHUDInstance->WeaponWidgets[WeaponCount]->TxtCurrentAmmo->SetText(AmmoText);

	AmmoText = FText::AsNumber(Weapon->WeaponStruct.GetMaxAmmo());
	InGameHUDInstance->WeaponWidgets[WeaponCount]->TxtMaxAmmo->SetText(AmmoText);
}
