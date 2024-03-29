// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "CharacterTypes.h"
#include "Interfaces/PickupInterface.h"
#include "MyCharacter.generated.h"

class UMyUserWidget;
class AWeapon;
class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;
class ASoul;
class ATreasure;

UCLASS()
class OPENWORLD_API AMyCharacter : public ABaseCharacter, public IPickupInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Attack() override;
	
	UFUNCTION(BlueprintCallable)
	void Disarm();

	UFUNCTION(BlueprintCallable)
	void Arm();
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Die() override;
	bool HasEnoughStamina();
	bool IsOccupied();
	virtual void SetOverlappingItem(AItem* Item) override;
	virtual void AddSouls(ASoul* Soul) override;
	virtual void AddGold(ATreasure* Treasure) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();

	UFUNCTION(BlueprintCallable)
	void HitReactEnd();
	
	virtual bool CanAttack() override;

private:
	
	void InitializeSlashOverlay();
	void SetHUDHealth();
	
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

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;
	
	UPROPERTY(VisibleAnywhere)
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	UPROPERTY(VisibleAnywhere)
	EActionState ActionState = EActionState::EAS_Unoccupied;

	UPROPERTY()
	UMyUserWidget* MyOverlay;
	
public:
	bool IsUnoccupied();
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
	FORCEINLINE EActionState GetActionState() const { return ActionState; }
};
