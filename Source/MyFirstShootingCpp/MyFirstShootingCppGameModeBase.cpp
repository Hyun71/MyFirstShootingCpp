// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyFirstShootingCppGameModeBase.h"
#include <Blueprint/UserWidget.h>
#include "ScoreWidget.h"
#include <Components/TextBlock.h>
#include "GameOverWidget.h"

void AMyFirstShootingCppGameModeBase::BeginPlay()
{
	//Score위젯을 생성해서
	scoreWidget = CreateWidget<UScoreWidget>(GetWorld(), scoreWidgetFactory);
	//화면에 출력하고 싶다.
	scoreWidget->AddToViewport();

	gameOverWidget = CreateWidget<UGameOverWidget>(GetWorld(), gameOverWidgetFactory);

	
	//마우스 보이지 않게 한다.
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);  //0번 플레이이 컨트롤러.

	//입력모드를 GameOnly로 한다.
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());  //월드와 스크린, 월드는 게임, 스크린은 UI. 포커스를 월드에 둘 것인지, UI둘 것인지, 둘 다 둘 것인지에 대해 결정하는 것.

	//GetWorld()->GetFirstPlayerController()->SetPause(true);  //일시정지.

}

void AMyFirstShootingCppGameModeBase::AddScore(int value)
{
	//점수를 누적하고싶다.
	score += value;
	scoreWidget->TextBlock_Score->SetText(FText::AsNumber(score));  //들어온 값을 문자로 바꾸어주는 것.
}

void AMyFirstShootingCppGameModeBase::ShowGameOverUI()
{
	gameOverWidget->AddToViewport();
	
	//마우스를 보이게 하고 싶다.
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);  //0번 플레이이 컨트롤러.

	//입력모드를 UIOnly로 하고 싶다.
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());  //월드와 스크린, 월드는 게임, 스크린은 UI. 포커스를 월드에 둘 것인지, UI둘 것인지, 둘 다 둘 것인지에 대해 결정하는 것.
}

