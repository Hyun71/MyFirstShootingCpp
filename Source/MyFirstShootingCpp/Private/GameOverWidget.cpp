// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

void UGameOverWidget::NativeConstruct()
{
	//버튼을 함수에 연결하고싶다.
	Button_Restart->OnClicked.AddDynamic(this, &UGameOverWidget::OnMyRestart);

	Button_Quit->OnClicked.AddDynamic(this, &UGameOverWidget::OnMyQuit);
}

void UGameOverWidget::OnMyRestart()
{
	FString levelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), FName(*levelName));
}

void UGameOverWidget::OnMyQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
