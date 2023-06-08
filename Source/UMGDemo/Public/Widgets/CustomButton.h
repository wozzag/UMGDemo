// Custom button class
#pragma once

#include "CoreMinimal.h"
#include "WidgetsBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "CustomButton.generated.h"

// Delegate for clicked/ hovered/ unhovered events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FButtonClickedSignature, class UCustomButton*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FButtonHoveredSignature, class UCustomButton*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FButtonUnHoveredSignature, class UCustomButton*, Button);

// Forward declarations
class UTextBlock;

UCLASS()
class UMGDEMO_API UCustomButton : public UWidgetsBase
{
	GENERATED_BODY()

public:

	// Bind the delegates
	FButtonClickedSignature OnClickedDelegate;

	FButtonClickedSignature OnHoveredDelegate;

	FButtonClickedSignature UnHoveredDelegate;

	// Bind the widgets
	UPROPERTY(meta = (BindWidget))
	UButton* CustomButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TxtButton;

protected:

	virtual void NativeConstruct() override;

	// Functions for clicked/ hovered/ unhovered
	UFUNCTION()
	void OnButtonClicked();

	UFUNCTION()
	void OnButtonHovered();

	UFUNCTION()
	void OnButtonUnHovered();
};