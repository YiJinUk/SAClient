// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/SA_UI_Game.h"
#include "SA_UI_GameOver.h"

#include "Components/TextBlock.h"

void USA_UI_Game::UIGameInit(ASA_PC* pc)
{
	_ui_game_over->UIGameOverInit(pc);
	_ui_game_over->SetVisibility(ESlateVisibility::Hidden);
}


void USA_UI_Game::UIGameSetVisibleGameOver(const ESlateVisibility e_ui_visible)
{
	_ui_game_over->SetVisibility(e_ui_visible);
}
void USA_UI_Game::SetHP(const int32 i_hp)
{
	_hp->SetText(FText::AsNumber(i_hp));
}