// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyFirstShootingCppGameModeBase.h"
#include <Blueprint/UserWidget.h>
#include "ScoreWidget.h"
#include <Components/TextBlock.h>

void AMyFirstShootingCppGameModeBase::BeginPlay()
{
	//Score������ �����ؼ�
	scoreWidget = CreateWidget<UScoreWidget>(GetWorld(), scoreWidgetFactory);
	//ȭ�鿡 ����ϰ� �ʹ�.
	scoreWidget->AddToViewport();
}

void AMyFirstShootingCppGameModeBase::AddScore(int value)
{
	//������ �����ϰ�ʹ�.
	score += value;
	scoreWidget->TextBlock_Score->SetText(FText::AsNumber(score));  //���� ���� ���ڷ� �ٲپ��ִ� ��.
}

