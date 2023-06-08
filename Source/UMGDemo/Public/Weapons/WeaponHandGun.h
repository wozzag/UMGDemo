// HandGun class

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "WeaponHandGun.generated.h"

UCLASS()
class UMGDEMO_API AWeaponHandGun : public AWeaponBase
{
	GENERATED_BODY()

	AWeaponHandGun();

public:

	// Overlap 
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
