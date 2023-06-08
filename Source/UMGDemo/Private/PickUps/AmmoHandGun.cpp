#include "PickUps/AmmoHandGun.h"
#include "Kismet/GameplayStatics.h"
#include "../UMGDemoCharacter.h"
#include "../UMGDemoPlayerController.h"

AAmmoHandGun::AAmmoHandGun()
{
    // Load the mesh/ set struct data / bind function
    static ConstructorHelpers::FObjectFinder<UStaticMesh> AmmoHandGunObj(TEXT("/Game/Meshes/SM_AmmoHandGun"));

    if (AmmoHandGunObj.Succeeded())
    {
        PickUpMesh->SetStaticMesh(AmmoHandGunObj.Object);
        PickUpStruct.PickUpAmount = 6;
        PickUpStruct.PickUpName = "AmmoHandGun";
        PickUpStruct.PickUpType = EPickUpType::EAmmoHandGun;
    }
    
    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AAmmoHandGun::OnOverlapBegin);
}

// If it is the player/ set the weapon ammo / update weapon widget ammo text/ destroy
void AAmmoHandGun::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        if (OtherActor->ActorHasTag("Player"))
        {
           AUMGDemoCharacter* UMGDemoCharacter = Cast<AUMGDemoCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
           AUMGDemoPlayerController* UMGDemoPlayerController = Cast<AUMGDemoPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

           for (int i = 0; i < UMGDemoCharacter->Weapons.Num(); i++)
           {
               if (UMGDemoCharacter->Weapons[i]->WeaponStruct.WeaponType == EWeaponType::EHandGun)
               {
                   if (UMGDemoCharacter->Weapons[i]->WeaponStruct.GetCurrentAmmo() < UMGDemoCharacter->Weapons[i]->WeaponStruct.GetMaxAmmo())
                   {
                       UMGDemoCharacter->Weapons[i]->WeaponStruct.SetCurrentAmmo(UMGDemoCharacter->Weapons[i]->WeaponStruct.GetCurrentAmmo() + this->PickUpStruct.PickUpAmount);
                       FText AmmoText = FText::AsNumber(UMGDemoCharacter->Weapons[i]->WeaponStruct.GetCurrentAmmo());

                       UMGDemoPlayerController->InGameHUDInstance->WeaponWidgets[i]->TxtCurrentAmmo->SetText(AmmoText);

                       Destroy();
                       break;
                   }
               }
           }
        }
    }
}