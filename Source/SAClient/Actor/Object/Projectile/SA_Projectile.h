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
	
public:
	//생성시 딱 한번만 호출합니다. 풀링에서 호출되지 않습니다
	void PROJPostInit(const FDataProjectile* s_data_proj);
	//풀에서 나올 때 마다 호출됩니다
	void PROJInit(const int64 i_id, const FVector& v_spawn_loc, const FVector2D& v2_velocity, const int32 i_yaw);
	void PROJMove(const float f_delta_time, const int32 i_move_speed);

	void PROJSetPoolActive(const bool b_is_active);

	FORCEINLINE const FInfoProjectile& GetInfoPROJ() const;
private:
	UPROPERTY()
		FInfoProjectile _info_proj;
};
