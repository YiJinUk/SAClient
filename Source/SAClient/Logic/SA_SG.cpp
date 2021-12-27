// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/SA_SG.h"

void USA_SG::SGSaveData(const FInfoPlayer& s_info_player)
{
	gold = s_info_player.GetGold();
	dmg = s_info_player.GetDMG();
	as = s_info_player.GetAS();
	shot_num = s_info_player.GetShotNumber();
	penetrate = s_info_player.GetPenetrate();
}