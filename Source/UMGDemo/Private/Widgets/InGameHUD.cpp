#include "Widgets/InGameHUD.h"

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
}
