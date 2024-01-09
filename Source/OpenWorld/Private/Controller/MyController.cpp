// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MyController.h"

#include "Input/MyEnhancedInputComponent.h"
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
}

void AMyController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyController::Move);
}

void AMyController::Move(const FInputActionValue& InputActionValue)
{
	const float InputAxis = InputActionValue.Get<float>();

	UE_LOG(LogTemp, Warning, TEXT("float : %f"), InputAxis);
}
