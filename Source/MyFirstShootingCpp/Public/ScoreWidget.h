// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTSHOOTINGCPP_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* TextBlock_ScoreTitle;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* TextBlock_Score;
};
