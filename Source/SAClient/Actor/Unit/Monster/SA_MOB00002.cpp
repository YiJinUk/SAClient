// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/Monster/SA_MOB00002.h"

void ASA_MOB00002::MOBPostInitChild(const FDataMonster* s_data_monster)
{
	_info_monster.is_split = true;
}