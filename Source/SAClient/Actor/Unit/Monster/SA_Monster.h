// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "Actor/Unit/SA_Unit.h"
#include "SA_Monster.generated.h"

class USA_UI_Headup_Monster;
class ASA_SpawnPoint;
class USA_GI;

/**
 * 
 */
UCLASS()
class SACLIENT_API ASA_Monster : public ASA_Unit
{
	GENERATED_BODY()
	
#pragma region Init
protected:
	ASA_Monster(FObjectInitializer const& object_initializer);

protected:
	UPROPERTY(EditAnywhere)
		class UWidgetComponent* _ui_headup = nullptr;
	UPROPERTY()
		USA_UI_Headup_Monster* _ui_headup_monster = nullptr;

	UPROPERTY()
		USA_GI* _sagi = nullptr;
#pragma endregion

#pragma region MOB
public:
	//생성시 딱 한번만 호출합니다. 풀링에서 호출되지 않습니다
	void MOBPostInit(const FDataMonster* s_data_monster);
	virtual void MOBPostInitChild(const FDataMonster* s_data_monster);
	//풀에서 나올 때 마다 호출됩니다
	void MOBInit(const int64 i_id, const EMonsterHP e_monster_hp, ASA_SpawnPoint* obj_spawn_point);
	void MOBInitClone(const int64 i_id, const EMonsterHP e_monster_hp, const FVector& s_spawn_loc, const FVector& v_velocity, const FRotator& r_rot);
	void MOBInitTreasureChest(const int64 i_id, const int32 i_hp, const int32 i_drop_gem, const FVector& s_spawn_loc);

	void MOBMove(const float f_delta_time);

	void MOBSetPoolActive(const bool b_is_active);
protected:
	virtual void MOBSetPoolActiveChild(const bool b_is_active);
private:
	void MOBTimerUIPool();
#pragma endregion

#pragma region Stat
public:
	/*
	* 체력을 변경합니다
	* i_change_hp : 변경될 체력의 수치입니다. 해당값으로 변경하는게 아닌 add, sub로 현재체력에서 계산해야합니다
	* b_is_add T : i_change_hp만큼 체력을 추가합니다
	* return : 계산결과 남은 체력값 입니다
	*/
	int32 MOBChangeHP(const int32 i_change_hp, int32& i_pure_dmg, const bool b_is_add = false);

	const FInfoMonster& GetInfoMonster() const;
	const EMonsterHP GetDownMonsterHP() const;

protected:
	UPROPERTY()
		FInfoMonster _info_monster;
#pragma endregion
};
