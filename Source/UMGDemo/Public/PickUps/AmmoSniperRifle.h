// SniperRifle pickup class

#pragma once

#include "CoreMinimal.h"
#include "PickUps/PickUpsBase.h"
#include "AmmoSniperRifle.generated.h"

UCLASS()
class UMGDEMO_API AAmmoSniperRifle : public APickUpsBase
{
	GENERATED_BODY()

	AAmmoSniperRifle();

public:

	// Overlap 
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
