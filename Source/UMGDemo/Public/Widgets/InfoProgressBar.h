// Info progress bar class

#pragma once

#include "CoreMinimal.h"
#include "WidgetsBase.h"
#include "Components/ProgressBar.h"
#include "InfoProgressBar.generated.h"

// Forward declaration
class UTextBlock;
class UImage;

UCLASS()
class UMGDEMO_API UInfoProgressBar : public UWidgetsBase
{
	GENERATED_BODY()

	UInfoProgressBar();

public:

	// Bind ProgressBar/ TextBlock/ Image
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TxtInfo;

	UPROPERTY(meta = (BindWidget))
	UImage* ImgInfoLine;

	// Array of InfoBar names
	TArray<FString> InfoBarNames;
};
