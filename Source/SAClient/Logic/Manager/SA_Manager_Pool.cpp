// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/SA_Manager_Pool.h"
#include "Logic/SA_GI.h"
#include "Actor/Unit/Monster/SA_Monster.h"
#include "Actor/Object/Projectile/SA_Projectile.h"

void ASA_Manager_Pool::PoolInit(USA_GI* sagi)
{
	_sagi = sagi;
	_spawn_param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	_pool_monster.Reserve(100);
}

ASA_Monster* ASA_Manager_Pool::PoolGetMonsterByCode(const FString& str_code_monster)
{
	return PoolOutMonster(str_code_monster);
}
ASA_Projectile* ASA_Manager_Pool::PoolGetPROJByCode(const FString& str_code_proj)
{
	return PoolOutPROJ(str_code_proj);
}

void ASA_Manager_Pool::PoolInMonster(ASA_Monster* monster)
{
	monster->MOBSetPoolActive(false);
	_pool_monster.FindOrAdd(monster->GetInfoMonster().code).Add(monster);
}
void ASA_Manager_Pool::PoolInPROJ(ASA_Projectile* proj)
{
	proj->PROJSetPoolActive(false);
	_pool_projectile.FindOrAdd(proj->GetInfoPROJ().code).Add(proj);
}

ASA_Monster* ASA_Manager_Pool::PoolOutMonster(const FString& str_code_monster)
{
	TArray<ASA_Monster*>* arr_pool_monster = _pool_monster.Find(str_code_monster);

	if (!arr_pool_monster || arr_pool_monster->Num() <= 0)
	{
		const FDataMonster* s_data_monster = _sagi->FindDataMonsterByCode(str_code_monster);
		ASA_Monster* monster_spawn = GetWorld()->SpawnActor<ASA_Monster>(s_data_monster->GetClassMonster(), _spawn_param); // 풀링 매니저
		monster_spawn->MOBPostInit(s_data_monster);
		return monster_spawn;
	}
	else
	{
		return arr_pool_monster->Pop();
	}
}
ASA_Projectile* ASA_Manager_Pool::PoolOutPROJ(const FString& str_code_proj)
{
	TArray<ASA_Projectile*>* arr_pool_proj = _pool_projectile.Find(str_code_proj);

	if (!arr_pool_proj || arr_pool_proj->Num() <= 0)
	{
		const FDataProjectile* s_data_proj = _sagi->FindDataPROJByCode(str_code_proj);
		ASA_Projectile* proj_spawn = GetWorld()->SpawnActor<ASA_Projectile>(s_data_proj->GetClassPROJ(), _spawn_param); // 풀링 매니저
		proj_spawn->PROJPostInit(s_data_proj);
		return proj_spawn;
	}
	else
	{
		return arr_pool_proj->Pop();
	}
}