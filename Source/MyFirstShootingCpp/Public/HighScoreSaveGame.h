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
	int32 save_highscore;
};
