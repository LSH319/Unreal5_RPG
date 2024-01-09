// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MyController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AMyController::AMyController()
{
}

void AMyController::BeginPlay()
{
	Super::BeginPlay();

	check(MyContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(MyContext, 0);
	}
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->bUseControllerRotationPitch = true;
		ControlledPawn->bUseControllerRotationRoll = true;
		ControlledPawn->bUseControllerRotationYaw = true;
	}
}

void AMyController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyController::Move);
	EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &AMyController::Turn);
	EnhancedInputComponent->BindAction(LookUpAction, ETriggerEvent::Triggered, this, &AMyController::LookUp);
}

void AMyController::Move(const FInputActionValue& InputActionValue)
{
	const float InputAxis = InputActionValue.Get<float>();
	
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ControlledPawn->GetActorForwardVector(), InputAxis);
	}
}

void AMyController::Turn(const FInputActionValue& InputActionValue)
{
	const float InputAxis = InputActionValue.Get<float>();

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(InputAxis);
	}
	
}

void AMyController::LookUp(const FInputActionValue& InputActionValue)
{
	const float InputAxis = InputActionValue.Get<float>();
	
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerPitchInput(InputAxis);
	}
}
