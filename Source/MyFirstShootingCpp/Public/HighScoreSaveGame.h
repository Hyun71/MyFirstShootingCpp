// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HighScoreSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTSHOOTINGCPP_API UHighScoreSaveGame : public USaveGame
{
	GENERATED_BODY()
public:

	UPROPERTY()  //UPROPERTY() 를 작성해주어야 언리얼에서 save값을 관리한다. 없으면 관리대상에서 벗어나서 무시해버린다.
	int32 save_highscore;
};
