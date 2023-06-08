#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Weapons/WeaponBase.h"
#include "UMGDemoCharacter.generated.h"

UCLASS(config=Game)
class AUMGDemoCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** SwitchWeapon Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwitchWeaponAction;

public:

	AUMGDemoCharacter();

	// Add weappon to array
	UFUNCTION()
	void AddWeapon(AWeaponBase* Weapon);

public:

	// DEBUGGING
	virtual void Tick(float DeltaTime) override;

	// Array of weapons
	TArray<AWeaponBase*> Weapons;

	// Switching weapon /Number of weapons  
	int32 CurrentWeapon;

	int32 WeaponCount;

	int32 MaxWeapons;

	// Used to prevent pickups unless all weapons are added to character
	bool HasMaxWeapons;

	// Health get/ set
	int32 GetCurrentHealth()
	{
		return CurrentHealth;
	}

	void SetCurrentHealth(int32 HealthAmount)
	{
		CurrentHealth = HealthAmount;
	}

	int32 GetMaxHealth()
	{
		return MaxHealth;
	}

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// SwitchWeapon input 
	void SwitchWeapon(const FInputActionValue& Value);

	// Health
	int32 MaxHealth;

	int32 CurrentHealth;

protected:

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

