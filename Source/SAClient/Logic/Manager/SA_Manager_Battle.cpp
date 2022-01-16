// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/SA_Manager_Battle.h"
#include "SA_Manager_VFX.h"
#include "Logic/SA_GM.h"
#include "Actor/Unit/Monster/SA_Monster.h"
#include "Actor/Object/Projectile/SA_Projectile.h"

void ASA_Manager_Battle::BattleInit(ASA_GM* sagm, ASA_Manager_VFX* manager_vfx)
{
	_sagm = sagm;
	_manager_vfx = manager_vfx;
}

bool ASA_Manager_Battle::BattleCalcStart(ASA_Projectile* proj, ASA_Monster* monster, const int32 i_dmg)
{
	if (!proj || !monster) return false;

	/*이펙트*/
	_manager_vfx->VFXStart(EVFXType::PROJ_HIT, proj->GetActorLocation());

	/*
	* 몬스터의 체력을 깎습니다
	* UI도 같이 업데이트 합니다
	*/
	bool b_is_monster_death = false;
	int32 i_pure_dmg = 0; // 몬스터에게 실제로 피해를 준 값
	int32 i_bonus = 0;
	int32 i_remain_hp = monster->MOBChangeHP(i_dmg, i_pure_dmg);

	/*몬스터가 죽었다면 풀링*/
	if (i_remain_hp <= 0)
	{
		i_bonus = monster->GetInfoMonster().bonus_gold;
		b_is_monster_death = true;

		/*Gem 획득*/
		_sagm->UpdateInfoWaveClearByGem(monster->GetInfoMonster().hp_max * 0.5f);
		_sagm->UpdateInfoWaveClearByKillEnemy();
	}
	else
	{
		b_is_monster_death = false;
	}

	_sagm->UpdateInfoWaveClearByScore(i_pure_dmg);

	/*Gem 획득*/
	if (monster->GetInfoMonster().is_treasure_chest)
		_sagm->UpdateInfoWaveClearByGem(i_bonus);

	/*발사체에게 공격에 성공했다고 알립니다*/
	proj->PROJAttackSuccess(monster->GetInfoMonster().id);

	return b_is_monster_death;
}