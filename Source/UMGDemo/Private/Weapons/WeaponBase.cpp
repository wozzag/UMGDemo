#include "Weapons/WeaponBase.h"
#include "Components/StaticMeshComponent.h"

AWeaponBase::AWeaponBase()
{
	// Collision component
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Capsule"));
	BoxCollision->SetBoxExtent(FVector(32.0f, 32.0f, 32.0f));
	RootComponent = BoxCollision;

	// StaticMesh component
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}
 