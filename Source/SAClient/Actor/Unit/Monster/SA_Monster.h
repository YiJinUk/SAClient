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
	//������ �� �ѹ��� ȣ���մϴ�. Ǯ������ ȣ����� �ʽ��ϴ�
	void MOBPostInit(const FDataMonster* s_data_monster);
	virtual void MOBPostInitChild(const FDataMonster* s_data_monster);
	//Ǯ���� ���� �� ���� ȣ��˴ϴ�
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
	* ü���� �����մϴ�
	* i_change_hp : ����� ü���� ��ġ�Դϴ�. �ش簪���� �����ϴ°� �ƴ� add, sub�� ����ü�¿��� ����ؾ��մϴ�
	* b_is_add T : i_change_hp��ŭ ü���� �߰��մϴ�
	* return : ����� ���� ü�°� �Դϴ�
	*/
	int32 MOBChangeHP(const int32 i_change_hp, int32& i_pure_dmg, const bool b_is_add = false);

	const FInfoMonster& GetInfoMonster() const;
	const EMonsterHP GetDownMonsterHP() const;

protected:
	UPROPERTY()
		FInfoMonster _info_monster;
#pragma endregion
};
