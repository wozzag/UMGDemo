// MachineGun class

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WeaponBase.h"
#include "WeaponMachineGun.generated.h"

UCLASS()
class UMGDEMO_API AWeaponMachineGun : public AWeaponBase
{
	GENERATED_BODY()
	
	AWeaponMachineGun();

public:

	// Overlap 
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
