// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/SA_Manager_Battle.h"
#include "Actor/Unit/Monster/SA_Monster.h"

void ASA_Manager_Battle::BattleCalcStart(ASA_Projectile* proj, ASA_Monster* monster, const int32 i_dmg)
{
	if (!proj || !monster) return;

	/*
	* 몬스터의 체력을 깎습니다
	* UI도 같이 업데이트 합니다
	*/
	int32 i_remain_hp = monster->MOBChangeHP(i_dmg);

	/*몬스터가 죽었다면 풀링*/
	if (i_remain_hp)
	{

	}
}