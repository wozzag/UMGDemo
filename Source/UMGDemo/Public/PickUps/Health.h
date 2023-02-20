// Health pickup class
#pragma once

#include "CoreMinimal.h"
#include "PickUps/PickUpsBase.h"
#include "Health.generated.h"

UCLASS()
class UMGDEMO_API AHealth : public APickUpsBase
{
	GENERATED_BODY()
	
	AHealth();

public:

	// Overlap 
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
