// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyFirstShootingCppGameModeBase.h"
#include <Blueprint/UserWidget.h>
#include "ScoreWidget.h"
#include <Components/TextBlock.h>
#include "GameOverWidget.h"

void AMyFirstShootingCppGameModeBase::BeginPlay()
{
	//Score������ �����ؼ�
	scoreWidget = CreateWidget<UScoreWidget>(GetWorld(), scoreWidgetFactory);
	//ȭ�鿡 ����ϰ� �ʹ�.
	scoreWidget->AddToViewport();

	gameOverWidget = CreateWidget<UGameOverWidget>(GetWorld(), gameOverWidgetFactory);

	
	//���콺 ������ �ʰ� �Ѵ�.
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);  //0�� �÷����� ��Ʈ�ѷ�.

	//�Է¸�带 GameOnly�� �Ѵ�.
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());  //����� ��ũ��, ����� ����, ��ũ���� UI. ��Ŀ���� ���忡 �� ������, UI�� ������, �� �� �� �������� ���� �����ϴ� ��.

	//GetWorld()->GetFirstPlayerController()->SetPause(true);  //�Ͻ�����.

}

void AMyFirstShootingCppGameModeBase::AddScore(int value)
{
	//������ �����ϰ�ʹ�.
	score += value;
	scoreWidget->TextBlock_Score->SetText(FText::AsNumber(score));  //���� ���� ���ڷ� �ٲپ��ִ� ��.
}

void AMyFirstShootingCppGameModeBase::ShowGameOverUI()
{
	gameOverWidget->AddToViewport();
	
	//���콺�� ���̰� �ϰ� �ʹ�.
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);  //0�� �÷����� ��Ʈ�ѷ�.

	//�Է¸�带 UIOnly�� �ϰ� �ʹ�.
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());  //����� ��ũ��, ����� ����, ��ũ���� UI. ��Ŀ���� ���忡 �� ������, UI�� ������, �� �� �� �������� ���� �����ϴ� ��.
}

