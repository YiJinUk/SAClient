// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/Monster/SA_Monster.h"

void ASA_Monster::MOBPostInit(const FString& str_code_monster)
{
	_info_monster.code = str_code_monster;
}

void ASA_Monster::MOBInit(const int64 i_id, const FVector& v_spawn_loc, const FVector& v_velocity, const FRotator& r_rot)
{
	_info_monster.id = i_id;
	_info_monster.velocity = v_velocity;
	_info_monster.rot = r_rot;

	SetActorRotation(_info_monster.rot);
	SetActorLocation(v_spawn_loc);
}

void ASA_Monster::MOBMove(const float f_delta_time)
{
	AddActorWorldOffset(_info_monster.velocity * 1000 * f_delta_time);
}

const FInfoMonster& ASA_Monster::GetInfoMonster() const { return _info_monster; }