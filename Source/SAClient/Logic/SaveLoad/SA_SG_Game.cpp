// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/SaveLoad/SA_SG_Game.h"

void USA_SG_Game::SGSaveData(const FInfoPlayer& s_info_player, const int32 i_wave_round)
{
	gold = s_info_player.GetGold();
	gem = s_info_player.GetGem();

	dmg = s_info_player.GetDMG();
	as = s_info_player.GetAS();
	shot_num = s_info_player.GetShotNumber();
	penetrate = s_info_player.GetPenetrate();

	wave_round = i_wave_round;
}