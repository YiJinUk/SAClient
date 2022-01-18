// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/SaveLoad/SA_SG_Game.h"

void USA_SG_Game::SGSaveData(const FInfoPlayer& s_info_player, const FInfoWave& s_info_wave)
{
	gem = s_info_player.GetGem();

	dmg = s_info_player.GetDMG();
	as = s_info_player.GetAS();
	shot_num = s_info_player.GetShotNumber();
	penetrate = s_info_player.GetPenetrate();

	cost_dmg_1 = s_info_player.GetUpgradeCostDMG();
	cost_as = s_info_player.GetUpgradeCostAS();
	cost_shot_num = s_info_player.GetUpgradeCostShotNumber();
	cost_penetrate = s_info_player.GetUpgradeCostPenetrate();

	wave_round = s_info_wave.wave_round;
	wave_monster_spawn_count_max = s_info_wave.monster_spawn_count_max;
	monster_hp = s_info_wave.monster_hp;
	monster_split_hp = s_info_wave.monster_split_hp;
}