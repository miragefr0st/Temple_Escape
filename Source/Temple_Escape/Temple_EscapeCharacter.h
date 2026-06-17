// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionStimuliSourceComponent.h"
#include  "PlayerInteraction_Interface.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Temple_EscapeCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, Health);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class ATemple_EscapeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UAIPerceptionStimuliSourceComponent* AIStimuliSource;

private:
	AActor* InteractObject; 
protected:
	/** Size of LineTrace for Interact Detection */
	UPROPERTY(EditAnywhere, Category="Character Movement: Walking")
	float MaxRunSpeed = 700.0f;
	bool _IsRunning = false;
	UPROPERTY(EditAnywhere, Category="Character Movement: Walking")
	float WalkSpeed = 300.0f;
	UPROPERTY(EditAnywhere, Category = "Character Movement: Walking")
	float JumpSpeedDebuf = 2.0f;
	UPROPERTY(EditAnywhere, Category="AI Perception")
	float RunNoiseMultiplier = 1.5;
	UPROPERTY(EditAnywhere, Category="AI Perception")
	float CrouchNoiseMultiplier = 0.;
	float _NoiseMultiplier = 1.;
	
	/** Size of LineTrace for Interact Detection */
	UPROPERTY(EditAnywhere, Category="Interact")
	float LineTraceLength = 1.0f;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	/** Interaction Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InteractAction;
	
	/** Interaction Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* CrouchAction;

	/** Interaction Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* RunAction;
public:

	/** Constructor */
	ATemple_EscapeCharacter();	

protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	
public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	/** Handles interact pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoInteract();
	
	/** Handles crouch pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoCrouch();

	/** Handles run pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoRun();

	/** Return if the player is running or not */
	UFUNCTION(BlueprintCallable, Category="Movement")
	bool IsRunning(){return _IsRunning;}

public:
	
	/** Return noise multiplier value. Base value is 1. */
	UFUNCTION(BlueprintCallable, Category="AI Perception")
	float GetCurrentNoiseMultiplier(){return _NoiseMultiplier;}

	UFUNCTION(BlueprintImplementableEvent, Category = "CPP Events")
	void Stretch();

	UFUNCTION(BlueprintImplementableEvent, Category = "CPP Events")
	void Squash();

public:
	/** Death dispatcher **/
	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;

	/** Health dispatcher **/
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

