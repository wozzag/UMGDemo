// PickUp base class

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PickUpsBase.generated.h"

// Forward declaration
class UStaticMeshComponent;

// Type of pickup
UENUM(BlueprintType)
enum class EPickUpType : uint8
{
	EAmmoHandGun,
	EAmmoMachineGun,
	EAmmoSniperRifle,
	EHealth
};

// PickUp struct / pickUp data 
USTRUCT(BlueprintType)
struct FPickUpStruct
{
	GENERATED_BODY()

	EPickUpType PickUpType;

	int32 PickUpAmount;

	FString PickUpName;
};

UCLASS()
class UMGDEMO_API APickUpsBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APickUpsBase();

	// Struct
	FPickUpStruct PickUpStruct;

	// Components
	UPROPERTY()
	UStaticMeshComponent* PickUpMesh;

	UPROPERTY()
	UBoxComponent* BoxCollision;
};
