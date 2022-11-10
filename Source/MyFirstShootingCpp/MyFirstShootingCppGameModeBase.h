// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyFirstShootingCppGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTSHOOTINGCPP_API AMyFirstShootingCppGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
//여기부터 전부 구현한 내용. 위로는 처음 생성되있었던 내용.
public:

	virtual void BeginPlay() override;

	int score;
	//highscore 추가.
	int highScore;

	void AddScore(int value);

	//SaveGame
	FString saveFileName;
	int32 saveUserIndex;

	//highScore값이 변하면 호출.
	void TrySaveGame(int32 value);
	//게임을 시작할 때 한 번 호출.
	int32 TryLoadGame();


	UPROPERTY(EditAnywhere)
	TSubclassOf<class UScoreWidget> scoreWidgetFactory;

	class UScoreWidget* scoreWidget;


	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameOverWidget> gameOverWidgetFactory;

	class UGameOverWidget* gameOverWidget;

	void ShowGameOverUI();  //이 함수를 호출하면 GameOver UI를 생성.
};
