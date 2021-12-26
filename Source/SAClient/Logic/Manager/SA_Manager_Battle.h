// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logic/Manager/SA_Manager_Master.h"
#include "SA_Manager_Battle.generated.h"

class ASA_GM;
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
	void BattleInit(ASA_GM* sagm);
private:
	UPROPERTY()
		ASA_GM* _sagm = nullptr;

public:
	/* return T : ���͸� óġ�ϴµ� �����߽��ϴ�*/
	bool BattleCalcStart(ASA_Projectile* proj, ASA_Monster* monster, const int32 i_dmg);
};
