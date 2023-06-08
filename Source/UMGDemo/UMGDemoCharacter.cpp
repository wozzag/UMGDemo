#include "UMGDemoCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "UMGDemoPlayerController.h"

AUMGDemoCharacter::AUMGDemoCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	// Weapon / Health variables default values
	WeaponCount = 0;
	CurrentWeapon = 0;
	MaxWeapons = 2;

	CurrentHealth = 0;
	MaxHealth = 100;

	// Find all actors of type AWeaponBase and bind the delegate
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWeaponBase::StaticClass(), FoundActors);

	for (int i = 0; i < FoundActors.Num(); i++)
	{
		AWeaponBase* Weapon = Cast<AWeaponBase>(FoundActors[i]);
		Weapon->WeaponAddedDelegate.AddDynamic(this, &ThisClass::AddWeapon);
	}
}

void AUMGDemoCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
 
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Input
void AUMGDemoCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUMGDemoCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUMGDemoCharacter::Look);

		//Switch Weapon
		EnhancedInputComponent->BindAction(SwitchWeaponAction, ETriggerEvent::Triggered, this, &AUMGDemoCharacter::SwitchWeapon);
	}
}

void AUMGDemoCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AUMGDemoCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
} 

// Add weapon once overlapped and received broadcast/ attach to character/ show the weapon widgets/ increment weaponcount
void AUMGDemoCharacter::AddWeapon(AWeaponBase* Weapon)
{
	if (WeaponCount == MaxWeapons)
	{
		HasMaxWeapons = true;
	}

	if (WeaponCount <= MaxWeapons)
	{
		Weapons.Add(Weapon);

		if (WeaponCount == 0)
		{
			Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "SCKTCurrentWeapon");
		}
		else
		{
			Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Weapon->WeaponStruct.WeaponSocketName);
		}

		AUMGDemoPlayerController* UMGDemoPlayerController = Cast<AUMGDemoPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

		UMGDemoPlayerController->InGameHUDInstance->ShowWeaponWidgets(WeaponCount, Weapon);

		WeaponCount++;
	}
}

// Switch the weapons/ switch opacity on the updated widgets
void AUMGDemoCharacter::SwitchWeapon(const FInputActionValue& Value)
{
	if (HasMaxWeapons)
	{
		Weapons[CurrentWeapon]->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Weapons[CurrentWeapon]->WeaponStruct.WeaponSocketName);
		
		AUMGDemoPlayerController* UMGDemoPlayerController = Cast<AUMGDemoPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

		UMGDemoPlayerController->InGameHUDInstance->WeaponWidgets[CurrentWeapon]->ImgWeapon->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.5f));

		if (CurrentWeapon == 2)
		{
			CurrentWeapon = -1;
		}
		
		CurrentWeapon++;

		UMGDemoPlayerController->InGameHUDInstance->WeaponWidgets[CurrentWeapon]->ImgWeapon->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		Weapons[CurrentWeapon]->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "SCKTCurrentWeapon");
		UMGDemoPlayerController->InGameHUDInstance->WeaponWidgets[CurrentWeapon]->PlayAnimationByName("AnimWeaponWidget",
			0.0f,
			1,
			EUMGSequencePlayMode::PingPong,
			1.0f);
	}
}

// DEBUGGING
void AUMGDemoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT(""));
}