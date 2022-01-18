// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/Monster/SA_MOB00010.h"

void ASA_MOB00010::MOBPostInitChild(const FDataMonster* s_data_monster)
{
	_info_monster.velocity = FVector(-1.f, 0.f, 0.f);
}