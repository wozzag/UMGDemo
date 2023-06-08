// Base weapon class

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "WeaponBase.generated.h"

// Delegate for overlap
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponAddedSignature, class AWeaponBase*, WeaponToAdd);

// Forward declaration
class UStaticMeshComponent;

// Type of weapon
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EHandGun,
	EMachineGun,
	ESniperRifle
};

// Weapon struct / weapon data / get/ set weapon ammo
USTRUCT(BlueprintType)
struct FWeaponStruct
{
    GENERATED_BODY()

    EWeaponType WeaponType;

    int32 MaxAmmo;

    int32 CurrentAmmo;

    FString WeaponName;

	UTexture2D* WeaponTexture;

	FName WeaponSocketName;

	int32 GetCurrentAmmo()
	{
		return CurrentAmmo;
	}

	void SetCurrentAmmo(int32 CurrentAmount)
	{
		CurrentAmmo = CurrentAmount;
	}

	int32 GetMaxAmmo()
	{
		return MaxAmmo;
	}

	void SetMaxAmmo(int32 MaxAmount)
	{
		MaxAmmo = MaxAmount;
	}
};

UCLASS()
class UMGDEMO_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	

	AWeaponBase();

	// Struct
	FWeaponStruct WeaponStruct;

	// Delegate
	FWeaponAddedSignature WeaponAddedDelegate;

protected:

	// Components
	UPROPERTY()
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY()
	UBoxComponent* BoxCollision;
};
