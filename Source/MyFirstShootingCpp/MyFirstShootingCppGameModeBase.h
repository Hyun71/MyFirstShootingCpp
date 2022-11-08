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
	void AddScore(int value);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UScoreWidget> scoreWidgetFactory;



	class UScoreWidget* scoreWidget;
};
