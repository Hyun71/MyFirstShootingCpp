// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyFirstShootingCppGameModeBase.h"
#include <Blueprint/UserWidget.h>
#include "ScoreWidget.h"
#include <Components/TextBlock.h>

void AMyFirstShootingCppGameModeBase::BeginPlay()
{
	//Score위젯을 생성해서
	scoreWidget = CreateWidget<UScoreWidget>(GetWorld(), scoreWidgetFactory);
	//화면에 출력하고 싶다.
	scoreWidget->AddToViewport();
}

void AMyFirstShootingCppGameModeBase::AddScore(int value)
{
	//점수를 누적하고싶다.
	score += value;
	scoreWidget->TextBlock_Score->SetText(FText::AsNumber(score));  //들어온 값을 문자로 바꾸어주는 것.
}

