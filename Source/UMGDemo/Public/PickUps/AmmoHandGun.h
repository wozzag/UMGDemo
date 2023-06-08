// HandGun pickup class

#pragma once

#include "CoreMinimal.h"
#include "PickUps/PickUpsBase.h"
#include "AmmoHandGun.generated.h"

UCLASS()
class UMGDEMO_API AAmmoHandGun : public APickUpsBase
{
	GENERATED_BODY()

	AAmmoHandGun();

public:

	// Overlap
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
