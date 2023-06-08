#include "Widgets/InGameHUD.h"

UInGameHUD::UInGameHUD()
{
	//Constructor helpers to load textures 
	static ConstructorHelpers::FObjectFinder<UTexture2D> TXRPBLineObj(TEXT("/Game/Textures/Widgets/TXRPBLine"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> TXRDistanceObj(TEXT("/Game/Textures/Widgets/TXRDistance"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> TXRMapObj(TEXT("/Game/Textures/Widgets/TXRMap"));

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
}

void UInGameHUD::NativeConstruct()
{
	Super::NativeConstruct();

	// Set weapon widgets and progress bars arrays
	WeaponWidgets.Add(WBP_WeaponPrimary);
	WeaponWidgets.Add(WBP_WeaponSecondary);
	WeaponWidgets.Add(WBP_WeaponTertiary);

	InfoProgressBars.Add(WBP_InfoProgressBarTop);
	InfoProgressBars.Add(WBP_InfoProgressBarMid);
	InfoProgressBars.Add(WBP_InfoProgressBarBtm);

	// Hide weapon widgets/ set textures/ text
	for (int i = 0; i < WeaponWidgets.Num(); i++)
	{
		WeaponWidgets[i]->SetVisibility(ESlateVisibility::Hidden);
	}

	ImgMap->SetBrushFromTexture(TXRMap);
	ImgDistance->SetBrushFromTexture(TXRDistance);

	FString DistanceString = "567";
	TxtDistance->SetText(FText::FromString(DistanceString));

	// Timerhandler for random progressbar percents
	GetWorld()->GetTimerManager().SetTimer(InfoBarTimerHandle, this, &UInGameHUD::SetInfoBarData, 0.2f, true);

	// Set progress bars and health bar text/ texture / color / line / scale
	FLinearColor ProgressBarColor = FLinearColor(0.16f, 0.72f, 0.7f, 1.0f);

	for (int i = 0; i < InfoProgressBars.Num(); i++)
	{
		InfoProgressBars[i]->TxtInfo->SetText(FText::FromString(InfoProgressBars[i]->InfoBarNames[i]));
		InfoProgressBars[i]->ImgInfoLine->SetBrushFromTexture(TXRPBLine);
		InfoProgressBars[i]->ProgressBar->SetFillColorAndOpacity(ProgressBarColor);
	}

	FWidgetTransform ProgressBarTransform = WBP_HealthProgressBar->ProgressBar->GetRenderTransform();
	ProgressBarTransform.Scale.Y = 3.0f;

	WBP_HealthProgressBar->TxtInfo->SetText(FText::FromString("Health"));
	WBP_HealthProgressBar->ProgressBar->SetRenderTransform(ProgressBarTransform);
	WBP_HealthProgressBar->ProgressBar->SetFillColorAndOpacity(ProgressBarColor);
	WBP_HealthProgressBar->ImgInfoLine->SetBrushFromTexture(TXRPBLine);
}

// Set random value for info progress bars
void UInGameHUD::SetInfoBarData()
{
	for (int i = 0; i < InfoProgressBars.Num(); i++)
	{
		float RandAmount = FMath::RandRange(0.0f, 1.0f);
		InfoProgressBars[i]->ProgressBar->SetPercent(RandAmount);
	}
}

// Show weapon widgets/ set opacity of other widgets/ play widget animation/ set the text 
void UInGameHUD::ShowWeaponWidgets(int32 WeaponCount, AWeaponBase* Weapon)
{
	if (WeaponCount == 0)
	{
		WeaponWidgets[WeaponCount]->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		WeaponWidgets[WeaponCount]->SetVisibility(ESlateVisibility::Visible);
		WeaponWidgets[WeaponCount]->ImgWeapon->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.5f));
	}

	WeaponWidgets[WeaponCount]->PlayAnimationByName("AnimWeaponWidget",
		0.0f,
		1,
		EUMGSequencePlayMode::PingPong,
		1.0f);

	WeaponWidgets[WeaponCount]->ImgWeapon->SetBrushFromTexture(Weapon->WeaponStruct.WeaponTexture);

	FText AmmoText = FText::AsNumber(Weapon->WeaponStruct.GetCurrentAmmo());
	WeaponWidgets[WeaponCount]->TxtCurrentAmmo->SetText(AmmoText);

	AmmoText = FText::AsNumber(Weapon->WeaponStruct.GetMaxAmmo());
	WeaponWidgets[WeaponCount]->TxtMaxAmmo->SetText(AmmoText);
}
