// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyFirstShootingCppGameModeBase.h"
#include <Blueprint/UserWidget.h>
#include "ScoreWidget.h"
#include <Components/TextBlock.h>
#include "GameOverWidget.h"
#include "HighScoreSaveGame.h"
#include <Kismet/GameplayStatics.h>

void AMyFirstShootingCppGameModeBase::BeginPlay()
{
	saveFileName = TEXT("HIGH_SCORE");
	saveUserIndex = 0;

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

	highScore = TryLoadGame();
	scoreWidget->TextBlock_HighScore->SetText(FText::AsNumber(highScore));

}

void AMyFirstShootingCppGameModeBase::AddScore(int value)
{
	//������ �����ϰ�ʹ�.
	score += value;
	scoreWidget->TextBlock_Score->SetText(FText::AsNumber(score));  //���� ���� ���ڷ� �ٲپ��ִ� ��.


	//HighScore ����
	//���� score > highscore ���, hightscore = score; �̴�. �׸��� UI���� �ݿ��ϰ� �ʹ�.
	if (score > highScore)
	{
		highScore = score;
		scoreWidget->TextBlock_HighScore->SetText(FText::AsNumber(highScore));  //���� ���� ���ڷ� �ٲپ��ִ� ��.

	 }
}

void AMyFirstShootingCppGameModeBase::TrySaveGame(int32 value)
{
	USaveGame* temp = UGameplayStatics::CreateSaveGameObject(UHighScoreSaveGame::StaticClass());

	UHighScoreSaveGame* saveInst = Cast<UHighScoreSaveGame>(temp);

	saveInst->save_highscore;

	UGameplayStatics::SaveGameToSlot(saveInst, saveFileName, saveUserIndex);
}
 
int32 AMyFirstShootingCppGameModeBase::TryLoadGame()
{
	if (false == UGameplayStatics::LoadGameFromSlot(saveFileName, saveUserIndex))
	{
		return 0;
	}
	USaveGame* temp = UGameplayStatics::LoadGameFromSlot(saveFileName, saveUserIndex);
	
	UHighScoreSaveGame* saveInst = Cast<UHighScoreSaveGame>(temp);
	return saveInst->save_highscore;
}

void AMyFirstShootingCppGameModeBase::ShowGameOverUI()
{
	gameOverWidget->AddToViewport();
	
	//���콺�� ���̰� �ϰ� �ʹ�.
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);  //0�� �÷����� ��Ʈ�ѷ�.

	//�Է¸�带 UIOnly�� �ϰ� �ʹ�.
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());  //����� ��ũ��, ����� ����, ��ũ���� UI. ��Ŀ���� ���忡 �� ������, UI�� ������, �� �� �� �������� ���� �����ϴ� ��.
}

