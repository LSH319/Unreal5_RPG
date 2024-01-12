// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterTypes.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class AWeapon;
class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;

UCLASS()
class OPENWORLD_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Disarm();

	UFUNCTION(BlueprintCallable)
	void Arm();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);
	
private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Hair;

	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Eyebrows;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AWeapon* EquippedWeapon;
	
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;
	
	UPROPERTY(VisibleAnywhere)
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	UPROPERTY(VisibleAnywhere)
	EActionState ActionState = EActionState::EAS_Unoccupied;
	
public:
	FORCEINLINE void SetOverlappingItem(AItem* Item){ OverlappingItem = Item; }
	FORCEINLINE AItem* GetOverlappingItem(){ return OverlappingItem; }
	
	FORCEINLINE void SetEquippedWeapon(AWeapon* NewWeapon){ EquippedWeapon = NewWeapon; }
	FORCEINLINE AWeapon* GetEquippedWeapon(){ return EquippedWeapon; }
	
	FORCEINLINE void SetCharacterState(ECharacterState NewCharacterState){ CharacterState = NewCharacterState; }
	UFUNCTION(BlueprintPure)
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE UAnimMontage* GetAttackMontage() const { return AttackMontage; }
	
	UFUNCTION(BlueprintPure)
	UAnimMontage* GetEquipMontage() const { return EquipMontage; }
	
	UFUNCTION(BlueprintCallable)
	void SetActionState(EActionState NewActionState)  { ActionState = NewActionState; }
	UFUNCTION(BlueprintPure)
	EActionState GetActionState() const { return ActionState; }
};
