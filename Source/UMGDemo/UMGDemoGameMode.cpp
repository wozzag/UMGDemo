#include "UMGDemoGameMode.h"
#include "UMGDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UMGDemoPlayerController.h"

AUMGDemoGameMode::AUMGDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Set the default player controller class
	PlayerControllerClass = AUMGDemoPlayerController::StaticClass();
}
