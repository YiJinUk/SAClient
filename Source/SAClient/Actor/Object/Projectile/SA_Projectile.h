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
	//������ �� �ѹ��� ȣ���մϴ�. Ǯ������ ȣ����� �ʽ��ϴ�
	void PROJPostInit(const FDataProjectile* s_data_proj);
	//Ǯ���� ���� �� ���� ȣ��˴ϴ�
	void PROJInit(const int64 i_id, const FVector& v_spawn_loc, const FVector2D& v2_velocity, const int32 i_yaw);
	//�����ߴ� �������� Ȯ���մϴ� return T : ������ �����Դϴ�
	bool PROJIsAttackedMonsterByMOBId(const int64 i_id_monster);
	void PROJMove(const float f_delta_time, const int32 i_move_speed);
	void PROJAttackSuccess(const int64 i_id_atk_monster);
	bool PROJIsDoPoolIn(const int8 i_proj_max_penetrate);

	void PROJSetPoolActive(const bool b_is_active);

	FORCEINLINE const FInfoProjectile& GetInfoPROJ() const;
private:
	UPROPERTY()
		FInfoProjectile _info_proj;

	//������ ������ ���̵� �����մϴ�. ������ �� ����մϴ�
	UPROPERTY()
		TSet<int64> _id_atk_monster;
};
