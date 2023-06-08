#include "Weapons/WeaponSniperRifle.h"

AWeaponSniperRifle::AWeaponSniperRifle()
{
    // Load the mesh and texture/ set struct data / bind function
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SniperRifleObj(TEXT("/Game/Meshes/SM_SniperRifle"));
    static ConstructorHelpers::FObjectFinder<UTexture2D> WeaponTextureObj(TEXT("/Game/Textures/Widgets/TXRSniperRifle"));

    if (SniperRifleObj.Succeeded())
    {
        WeaponMesh->SetStaticMesh(SniperRifleObj.Object);
        WeaponStruct.MaxAmmo = 6;
        WeaponStruct.CurrentAmmo = 0;
        WeaponStruct.WeaponName = "SniperRifle";
        WeaponStruct.WeaponSocketName = "SCKTSniperRifle";
        WeaponStruct.WeaponType = EWeaponType::ESniperRifle;
        WeaponStruct.WeaponTexture = WeaponTextureObj.Object;
    }

    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponSniperRifle::OnOverlapBegin);
}

// If it is the player/ broadcast to player character AddWeapon() function
void AWeaponSniperRifle::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        if (OtherActor->ActorHasTag("Player"))
        {
            WeaponAddedDelegate.Broadcast(this);
        }
    }
}
