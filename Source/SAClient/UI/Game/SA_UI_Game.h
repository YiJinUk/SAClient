// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "UI/SA_UI_Master.h"
#include "SA_UI_Game.generated.h"

class ASA_PC;
class USA_UI_GameOver;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_UI_Game : public USA_UI_Master
{
	GENERATED_BODY()

public:
	void UIGameInit(ASA_PC* pc);

public:
	void UIGameSetVisibleGameOver(const ESlateVisibility e_ui_visible);
	
private:
	UPROPERTY(Meta = (BindWidget))
		USA_UI_GameOver* _ui_game_over = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _hp = nullptr;

public:
	FORCEINLINE void SetHP(const int32 i_hp);
};
