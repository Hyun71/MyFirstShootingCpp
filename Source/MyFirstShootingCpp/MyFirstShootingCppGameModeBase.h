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
	
//������� ���� ������ ����. ���δ� ó�� �������־��� ����.
public:

	virtual void BeginPlay() override;

	int score;
	//highscore �߰�.
	int highScore;

	void AddScore(int value);

	//SaveGame
	FString saveFileName;
	int32 saveUserIndex;

	//highScore���� ���ϸ� ȣ��.
	void TrySaveGame(int32 value);
	//������ ������ �� �� �� ȣ��.
	int32 TryLoadGame();


	UPROPERTY(EditAnywhere)
	TSubclassOf<class UScoreWidget> scoreWidgetFactory;

	class UScoreWidget* scoreWidget;


	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameOverWidget> gameOverWidgetFactory;

	class UGameOverWidget* gameOverWidget;

	void ShowGameOverUI();  //�� �Լ��� ȣ���ϸ� GameOver UI�� ����.
};
