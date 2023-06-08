#include "PickUps/AmmoSniperRifle.h"
#include "Kismet/GameplayStatics.h"
#include "../UMGDemoCharacter.h"
#include "../UMGDemoPlayerController.h"

AAmmoSniperRifle::AAmmoSniperRifle()
{
    // Load the mesh/ set struct data / bind function
    static ConstructorHelpers::FObjectFinder<UStaticMesh> AmmoSniperRifleObj(TEXT("/Game/Meshes/SM_AmmoSniperRifle"));

    if (AmmoSniperRifleObj.Succeeded())
    {
        PickUpMesh->SetStaticMesh(AmmoSniperRifleObj.Object);
        PickUpStruct.PickUpAmount = 2;
        PickUpStruct.PickUpName = "SniperRifle";
        PickUpStruct.PickUpType = EPickUpType::EAmmoSniperRifle;
    }

    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AAmmoSniperRifle::OnOverlapBegin);
}

// If it is the player/ set the weapon ammo / update weapon widget ammo text/ destroy
void AAmmoSniperRifle::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        if (OtherActor->ActorHasTag("Player"))
        {
            AUMGDemoCharacter* UMGDemoCharacter = Cast<AUMGDemoCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
            AUMGDemoPlayerController* UMGDemoPlayerController = Cast<AUMGDemoPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

            for (int i = 0; i < UMGDemoCharacter->Weapons.Num(); i++)
            {
                if (UMGDemoCharacter->Weapons[i]->WeaponStruct.WeaponType == EWeaponType::ESniperRifle)
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