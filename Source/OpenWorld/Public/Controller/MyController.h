// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class OPENWORLD_API AMyController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void PlayEquipMontage(FName SectionName);
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> MyContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> TurnAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookUpAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> EquipAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> AttackAction;
	
	void Move(const FInputActionValue& InputActionValue);
	void Turn(const FInputActionValue& InputActionValue);
	void LookUp(const FInputActionValue& InputActionValue);
	void Jump(const FInputActionValue& InputActionValue);
	void Equip(const FInputActionValue& InputActionValue);
	void Attack(const FInputActionValue& InputActionValue);
};
