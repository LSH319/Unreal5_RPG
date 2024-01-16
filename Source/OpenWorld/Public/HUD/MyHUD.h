// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

class UMyUserWidget;

/**
 * 
 */
UCLASS()
class OPENWORLD_API AMyHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Slash)
	TSubclassOf<UMyUserWidget> MyOverlayClass;

	UPROPERTY()
	UMyUserWidget* MyOverlay;

public:
	FORCEINLINE UMyUserWidget* GetMyOverlay() const { return MyOverlay; }
};
