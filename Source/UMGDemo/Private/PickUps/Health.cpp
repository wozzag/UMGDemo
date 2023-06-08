#include "PickUps/Health.h"
#include "Kismet/GameplayStatics.h"
#include "../UMGDemoCharacter.h"
#include "../UMGDemoPlayerController.h"

AHealth::AHealth()
{
    // Load the mesh/ set struct data / bind function
    static ConstructorHelpers::FObjectFinder<UStaticMesh> HealthObj(TEXT("/Game/Meshes/SM_Health"));

    if (HealthObj.Succeeded())
    {
        PickUpMesh->SetStaticMesh(HealthObj.Object);
        PickUpStruct.PickUpAmount = 20;
        PickUpStruct.PickUpName = "Health";
        PickUpStruct.PickUpType = EPickUpType::EHealth;
    }

    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AHealth::OnOverlapBegin);
}

// If it is the player/ set health/ update health bar/ destroy
void AHealth::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        if (OtherActor->ActorHasTag("Player"))
        {
            AUMGDemoCharacter* UMGDemoCharacter = Cast<AUMGDemoCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
            AUMGDemoPlayerController* UMGDemoPlayerController = Cast<AUMGDemoPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

           if (UMGDemoCharacter->GetCurrentHealth() >= UMGDemoCharacter->GetMaxHealth())
           {
                return;
           }
           else
           {
                int32 Health = UMGDemoCharacter->GetCurrentHealth() + PickUpStruct.PickUpAmount;
                UMGDemoCharacter->SetCurrentHealth(Health);

                UMGDemoPlayerController->InGameHUDInstance->WBP_HealthProgressBar->ProgressBar->SetPercent(float(UMGDemoCharacter->GetCurrentHealth() / 100.0f));

                Destroy();
           }
        }
    }
}