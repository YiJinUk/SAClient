// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "Actor/Object/SA_Object.h"
#include "SA_Projectile.generated.h"

/**
 * 
 */
UCLASS()
class SACLIENT_API ASA_Projectile : public ASA_Object
{
	GENERATED_BODY()

protected:
	ASA_Projectile();
protected:
	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* _particle = nullptr;
	
public:
	//생성시 딱 한번만 호출합니다. 풀링에서 호출되지 않습니다
	void PROJPostInit(const FDataProjectile* s_data_proj);
	//풀에서 나올 때 마다 호출됩니다
	void PROJInit(const int64 i_id, const FVector& v_spawn_loc, const FVector2D& v2_velocity, const int32 i_yaw);
	//공격했던 몬스터인지 확인합니다 return T : 공격한 몬스터입니다
	bool PROJIsAttackedMonsterByMOBId(const int64 i_id_monster);
	void PROJMove(const float f_delta_time, const int32 i_move_speed);
	void PROJAttackSuccess(const int64 i_id_atk_monster);
	bool PROJIsDoPoolIn(const int8 i_proj_max_penetrate);

	void PROJSetPoolActive(const bool b_is_active);

	FORCEINLINE const FInfoProjectile& GetInfoPROJ() const;
private:
	UPROPERTY()
		FInfoProjectile _info_proj;

	//공격한 몬스터의 아이디를 저장합니다. 관통할 때 사용합니다
	UPROPERTY()
		TSet<int64> _id_atk_monster;
};
