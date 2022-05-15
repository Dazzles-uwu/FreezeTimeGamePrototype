// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Player = Cast<ADaffaBuckleyA3Character>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void UHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Player)
	{
		HealthBar->SetPercent(Player->Health/10);
		FNumberFormattingOptions Opts;
		Opts.SetMaximumFractionalDigits(0);
		CurrentHealthLabel->SetText(FText::AsNumber(Player->Health, &Opts));
	}
}
