// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logic/Manager/SA_Manager_Master.h"
#include "SA_Manager_Battle.generated.h"

class ASA_Manager_VFX;
class ASA_GM;
class ASA_PC;
class ASA_Projectile;
class ASA_Monster;

/**
 * 
 */
UCLASS()
class SACLIENT_API ASA_Manager_Battle : public ASA_Manager_Master
{
	GENERATED_BODY()

public:
	void BattleInit(ASA_GM* sagm, ASA_PC* pc, ASA_Manager_VFX* manager_vfx);
private:
	UPROPERTY()
		ASA_GM* _sagm = nullptr;
	UPROPERTY()
		ASA_PC* _pc = nullptr;
	UPROPERTY()
		ASA_Manager_VFX* _manager_vfx = nullptr;

public:
	/* return T : 몬스터를 처치하는데 성공했습니다*/
	bool BattleCalcStart(ASA_Projectile* proj, ASA_Monster* monster, const int32 i_dmg);
};
