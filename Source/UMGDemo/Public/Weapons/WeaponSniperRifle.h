// Sniper rifle class

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WeaponBase.h"
#include "WeaponSniperRifle.generated.h"

UCLASS()
class UMGDEMO_API AWeaponSniperRifle : public AWeaponBase
{
	GENERATED_BODY()

	AWeaponSniperRifle();

public:

	// Overlap 
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
