// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DaffaBuckleyA3Character.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DAFFABUCKLEYA3_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentHealthLabel;

	ADaffaBuckleyA3Character* Player;

	void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
