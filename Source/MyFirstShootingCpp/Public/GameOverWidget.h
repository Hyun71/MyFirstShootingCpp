// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTSHOOTINGCPP_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;  //위젯은 NativeConstruct가 시작.

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Button_Restart;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Button_Quit;
	
	UFUNCTION()
	void OnMyRestart();
	UFUNCTION()
	void OnMyQuit();
};
