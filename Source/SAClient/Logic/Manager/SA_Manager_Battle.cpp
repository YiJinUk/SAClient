// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/SA_Manager_Battle.h"
#include "SA_Manager_VFX.h"
#include "Logic/SA_GM.h"
#include "Logic/SA_PC.h"
#include "Actor/Unit/Monster/SA_Monster.h"
#include "Actor/Object/Projectile/SA_Projectile.h"

void ASA_Manager_Battle::BattleInit(ASA_GM* sagm, ASA_PC* pc, ASA_Manager_VFX* manager_vfx)
{
	_sagm = sagm;
	_pc = pc;
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
	//int32 i_obtain = 0;
	int32 i_remain_hp = monster->MOBChangeHP(i_dmg, i_pure_dmg);

	/*몬스터가 죽었다면 풀링*/
	if (i_remain_hp <= 0)
	{
		b_is_monster_death = true;		
		_sagm->MonsterDeath(monster);
		//_sagm->UpdateInfoWaveClearByKillEnemy();

		///*Gem 획득*/
		//if (monster->GetInfoMonster().is_treasure_chest)
		//{
		//	/*Gem 획득*/
		//	i_obtain = monster->GetInfoMonster().bonus_gold;
		//}
		//else
		//{
		//	i_obtain = monster->GetInfoMonster().hp_max * 0.5f;
		//}

		//if (i_obtain <= 0)
		//	i_obtain = 1;

		//_sagm->UpdateInfoWaveClearByGem(i_obtain);
		//_pc->PCKillMonster(monster->GetActorLocation(), i_obtain);
	}
	else
	{
		b_is_monster_death = false;
	}

	//_sagm->UpdateInfoWaveClearByScore(i_pure_dmg);



	/*발사체에게 공격에 성공했다고 알립니다*/
	proj->PROJAttackSuccess(monster->GetInfoMonster().id);

	return b_is_monster_death;
}