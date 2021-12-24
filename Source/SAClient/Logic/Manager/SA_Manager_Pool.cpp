// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/SA_Manager_Pool.h"
#include "Actor/Unit/Monster/SA_Monster.h"

void ASA_Manager_Pool::PoolInit()
{
	_pool_monster.Reserve(100);
}

ASA_Monster* ASA_Manager_Pool::PoolGetMonsterByCode(const FString& str_code_monster)
{
	return PoolOutMonster(str_code_monster);
}

void ASA_Manager_Pool::PoolInMonster(ASA_Monster* monster)
{
	monster->SetActorLocation(FVector(0.f, 0.f, -500.f));
	_pool_monster.FindOrAdd(monster->GetInfoMonster().code).Add(monster);
}

ASA_Monster* ASA_Manager_Pool::PoolOutMonster(const FString& str_code_monster)
{
	TArray<ASA_Monster*>* arr_pool_monster = _pool_monster.Find(str_code_monster);

	if (!arr_pool_monster || arr_pool_monster->Num() <= 0)
	{
		ASA_Monster* monster_spawn = PoolSpawnMonster(str_code_monster);
		monster_spawn->MOBPostInit(str_code_monster);
		return monster_spawn;
	}
	else
	{
		return arr_pool_monster->Pop();
	}
}