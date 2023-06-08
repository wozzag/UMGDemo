#include "Widgets/CustomButton.h"

// Bind click / hovered/ unhovered function to the buttons
void UCustomButton::NativeConstruct()
{
	Super::NativeConstruct();

	CustomButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnButtonClicked);
	CustomButton->OnHovered.AddUniqueDynamic(this, &ThisClass::OnButtonHovered);
	CustomButton->OnUnhovered.AddUniqueDynamic(this, &ThisClass::OnButtonUnHovered);
}

// Broadcast the click event
void UCustomButton::OnButtonClicked()
{
	OnClickedDelegate.Broadcast(this);
}

// Broadcast the hovered event
void UCustomButton::OnButtonHovered()
{
	OnHoveredDelegate.Broadcast(this);
}

// Broadcast the unhovered event
void UCustomButton::OnButtonUnHovered()
{
	UnHoveredDelegate.Broadcast(this);
}
