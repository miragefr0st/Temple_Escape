// Copyright Epic Games, Inc. All Rights Reserved.

#include "Temple_EscapeCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Temple_Escape.h"

ATemple_EscapeCharacter::ATemple_EscapeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Create AIPerception Stimuli Source
	AIStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIStimuliSource"));

	InteractObject = nullptr;
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ATemple_EscapeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATemple_EscapeCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ATemple_EscapeCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATemple_EscapeCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ATemple_EscapeCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATemple_EscapeCharacter::Look);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ATemple_EscapeCharacter::DoInteract);

		// Holding Interact
		EnhancedInputComponent->BindAction(HoldInteractAction, ETriggerEvent::Started, this, &ATemple_EscapeCharacter::DoHoldInteract);

		// Released Interact
		EnhancedInputComponent->BindAction(ReleaseInteractAction, ETriggerEvent::Started, this, &ATemple_EscapeCharacter::DoReleasedInteract);
		
		// Crouch
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ATemple_EscapeCharacter::DoCrouch);

		// Run
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &ATemple_EscapeCharacter::DoRun);
	}
	else
	{
		UE_LOG(LogTemple_Escape, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATemple_EscapeCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void ATemple_EscapeCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ATemple_EscapeCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ATemple_EscapeCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ATemple_EscapeCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
	Stretch();
	GetCharacterMovement()->MaxWalkSpeed = _IsRunning ? MaxRunSpeed/JumpSpeedDebuf : WalkSpeed/JumpSpeedDebuf;

}

void ATemple_EscapeCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
	GetCharacterMovement()->MaxWalkSpeed = _IsRunning ? MaxRunSpeed : WalkSpeed;
}

void ATemple_EscapeCharacter::DoInteract()
{
	/*Antipode LineTrace Example: https://dev.epicgames.com/community/snippets/2rR/simple-c-line-trace-collision-query*/

	FHitResult Hit;
	
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * LineTraceLength;
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Vehicle, QueryParams);
	
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 5.0f);
 
	// If the trace hit something, bBlockingHit will be true,
	// and its fields will be filled with detailed info about what was hit
	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		Cast<IPlayerInteraction_Interface>(Hit.GetActor())->Execute_Interact(Hit.GetActor());
		InteractObject = Hit.GetActor();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, "Interact hit: "+Hit.GetActor()->GetName());
	}
}

void ATemple_EscapeCharacter::DoHoldInteract()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, "Interact hold ");
	if (InteractObject != nullptr)
	{Cast<IPlayerInteraction_Interface>(InteractObject)->Execute_HoldInteract(InteractObject);}
}

void ATemple_EscapeCharacter::DoReleasedInteract()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, "Interact release ");
	if (InteractObject != nullptr)
	{Cast<IPlayerInteraction_Interface>(InteractObject)->Execute_ReleasedInteract(InteractObject);}
	InteractObject = nullptr;
}

void ATemple_EscapeCharacter::DoCrouch()
{
	if (IsCrouched())
	{
		UnCrouch();
		_NoiseMultiplier = 1.;
	}
	else
	{
		GetCharacterMovement() -> MaxWalkSpeed = WalkSpeed;
		_IsRunning = false;
		Crouch();
		_NoiseMultiplier = CrouchNoiseMultiplier;
	}
}

void ATemple_EscapeCharacter::DoRun()
{
	if (_IsRunning)
	{
		GetCharacterMovement() -> MaxWalkSpeed = WalkSpeed;
		_IsRunning = false;
		_NoiseMultiplier = 1.;
	}
	else
	{
		if (IsCrouched())
		{
			UnCrouch();
		}
		GetCharacterMovement() -> MaxWalkSpeed = MaxRunSpeed;
		_IsRunning = true;
		_NoiseMultiplier = RunNoiseMultiplier;
	}
}