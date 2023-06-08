
#include "Widgets/InfoProgressBar.h"

UInfoProgressBar::UInfoProgressBar()
{
	Super::NativeConstruct();

	// Text for the info bar
	InfoBarNames.Add("Air");
	InfoBarNames.Add("Wind");
	InfoBarNames.Add("Temp");
}
