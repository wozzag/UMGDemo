#include "Weapons/WeaponMachineGun.h"

AWeaponMachineGun::AWeaponMachineGun()
{
    // Load the mesh and texture/ set struct data / bind function
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MachineGunObj(TEXT("/Game/Meshes/SM_MachineGun"));
    static ConstructorHelpers::FObjectFinder<UTexture2D> WeaponTextureObj(TEXT("/Game/Textures/Widgets/TXRMachineGun"));
   
    if (MachineGunObj.Succeeded())
    {
        WeaponMesh->SetStaticMesh(MachineGunObj.Object);
        WeaponStruct.MaxAmmo = 24;
        WeaponStruct.CurrentAmmo = 0;
        WeaponStruct.WeaponName = "";
        WeaponStruct.WeaponSocketName = "SCKTMachineGun";
        WeaponStruct.WeaponType = EWeaponType::EMachineGun;
        WeaponStruct.WeaponTexture = WeaponTextureObj.Object;
    }

    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponMachineGun::OnOverlapBegin);
}

// If it is the player/ broadcast to player character AddWeapon() function
void AWeaponMachineGun::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        if (OtherActor->ActorHasTag("Player"))
        {
            WeaponAddedDelegate.Broadcast(this);
        }
    }
}
