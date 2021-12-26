// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SA_Manager_Master.h"
#include "SA_Manager_Pool.generated.h"

class USA_GI;
class ASA_Monster;

UCLASS()
class SACLIENT_API ASA_Manager_Pool : public ASA_Manager_Master
{
	GENERATED_BODY()

public:
	void PoolInit(USA_GI* sagi);

public:
	ASA_Monster* PoolGetMonsterByCode(const FString& str_code_monster);

	void PoolInMonster(ASA_Monster* monster);
protected:
	UFUNCTION(BlueprintImplementableEvent)
		ASA_Monster* PoolSpawnMonster(TSubclassOf<ASA_Monster> class_monster);
private:
	ASA_Monster* PoolOutMonster(const FString& str_code_monster);
private:
	UPROPERTY()
		USA_GI* _sagi = nullptr;


	FActorSpawnParameters _spawn_param = FActorSpawnParameters();

	TMap<FString, TArray<ASA_Monster*>> _pool_monster;
};
