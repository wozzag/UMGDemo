#include "PickUps/PickUpsBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickUpsBase::APickUpsBase()
{
	// Collision component
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetBoxExtent(FVector(32.0f, 32.0f, 32.0f));
	RootComponent = BoxCollision;

    // StaticMeshComponent
    PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUpMesh"));
    PickUpMesh->SetupAttachment(RootComponent);
}