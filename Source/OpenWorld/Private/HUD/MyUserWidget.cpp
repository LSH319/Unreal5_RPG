// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MyUserWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMyUserWidget::SetHealthBarPercent(float Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);
	}
}

void UMyUserWidget::SetStaminaBarPercent(float Percent)
{
	if (StaminaProgressBar)
	{
		StaminaProgressBar->SetPercent(Percent);
	}
}

void UMyUserWidget::SetGold(int32 Gold)
{
	if (GoldCount)
	{
		const FString String = FString::Printf(TEXT("%d"), Gold);
		const FText Text = FText::FromString(String);
		GoldCount->SetText(Text);
	}
}

void UMyUserWidget::SetSouls(int32 Souls)
{
	if (SoulCount)
	{
		const FString String = FString::Printf(TEXT("%d"), Souls);
		const FText Text = FText::FromString(String);
		SoulCount->SetText(Text);
	}
}