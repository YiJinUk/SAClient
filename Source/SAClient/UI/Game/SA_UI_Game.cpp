// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/SA_UI_Game.h"

#include "Components/TextBlock.h"

void USA_UI_Game::UIPlayerUpdateCheck(const FInfoPlayer& s_info_player_new, const FInfoPlayer& s_info_player_old)
{
	if (s_info_player_new.hp != s_info_player_old.hp)
	{
		SetHP(s_info_player_new.hp);
	}
}

void USA_UI_Game::SetHP(const int32 i_hp)
{
	_hp->SetText(FText::AsNumber(i_hp));
}