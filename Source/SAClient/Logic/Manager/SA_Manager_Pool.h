// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SA_Manager_Master.h"
#include "SA_Manager_Pool.generated.h"

class ASA_Monster;

UCLASS()
class SACLIENT_API ASA_Manager_Pool : public ASA_Manager_Master
{
	GENERATED_BODY()

public:
	void PoolInit();

public:
	ASA_Monster* PoolGetMonsterByCode(const FString& str_code_monster);

	void PoolInMonster(ASA_Monster* monster);
protected:
	UFUNCTION(BlueprintImplementableEvent)
		ASA_Monster* PoolSpawnMonster(const FString& str_code_monster);
private:
	ASA_Monster* PoolOutMonster(const FString& str_code_monster);
private:
	TMap<FString, TArray<ASA_Monster*>> _pool_monster;
};
