// MachineGun pickup class

#pragma once

#include "CoreMinimal.h"
#include "PickUps/PickUpsBase.h"
#include "AmmoMachineGun.generated.h"

UCLASS()
class UMGDEMO_API AAmmoMachineGun : public APickUpsBase
{
	GENERATED_BODY()

	AAmmoMachineGun();

public:

	// Overlap 
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
