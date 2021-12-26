// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/SA_Manager_Battle.h"
#include "Logic/SA_GM.h"
#include "Actor/Unit/Monster/SA_Monster.h"

void ASA_Manager_Battle::BattleInit(ASA_GM* sagm)
{
	_sagm = sagm;
}

bool ASA_Manager_Battle::BattleCalcStart(ASA_Projectile* proj, ASA_Monster* monster, const int32 i_dmg)
{
	if (!proj || !monster) return false;

	/*
	* 몬스터의 체력을 깎습니다
	* UI도 같이 업데이트 합니다
	*/
	bool b_is_monster_death = false;
	int32 i_pure_dmg = 0; // 몬스터에게 실제로 피해를 준 값
	int32 i_remain_hp = monster->MOBChangeHP(i_dmg, i_pure_dmg);	

	/*몬스터가 죽었다면 풀링*/
	if (i_remain_hp <= 0)
	{
		i_pure_dmg += monster->GetInfoMonster().bonus_gold;
		b_is_monster_death = true;
	}
	else
	{
		b_is_monster_death = false;
	}


	/*골드 획득*/
	_sagm->PlayerChangeGold(i_pure_dmg, true);

	return b_is_monster_death;
}