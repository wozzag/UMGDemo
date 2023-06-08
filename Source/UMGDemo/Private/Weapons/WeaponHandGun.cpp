#include "Weapons/WeaponHandGun.h"

AWeaponHandGun::AWeaponHandGun()
{
    // Load the mesh and texture/ set struct data / bind function
    static ConstructorHelpers::FObjectFinder<UStaticMesh> HandGunObj(TEXT("/Game/Meshes/SM_HandGun"));
    static ConstructorHelpers::FObjectFinder<UTexture2D> WeaponTextureObj(TEXT("/Game/Textures/Widgets/TXRHandGun"));
    
    if (HandGunObj.Succeeded() && WeaponTextureObj.Succeeded())
    {
        WeaponMesh->SetStaticMesh(HandGunObj.Object);
        WeaponStruct.MaxAmmo = 12;
        WeaponStruct.CurrentAmmo = 0;
        WeaponStruct.WeaponName = "HandGun";
        WeaponStruct.WeaponSocketName = "SCKTHandGun";
        WeaponStruct.WeaponType = EWeaponType::EHandGun;
        WeaponStruct.WeaponTexture = WeaponTextureObj.Object;
    }

    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponHandGun::OnOverlapBegin);
}

// If it is the player/ broadcast to player character AddWeapon() function
void AWeaponHandGun::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        if (OtherActor->ActorHasTag("Player"))
        {
            WeaponAddedDelegate.Broadcast(this);
        }
    }
}
