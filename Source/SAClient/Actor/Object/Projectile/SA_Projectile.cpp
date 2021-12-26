// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/Projectile/SA_Projectile.h"
#include "Logic/SA_FunctionLibrary.h"

void ASA_Projectile::PROJPostInit(const FDataProjectile* s_data_proj)
{
	if (!s_data_proj) return;
	_info_proj.code = s_data_proj->GetCode();
}

void ASA_Projectile::PROJInit(const int64 i_id, const FVector& v_spawn_loc, const FVector2D& v2_velocity, const int32 i_yaw)
{
	/*풀링*/
	PROJSetPoolActive(true);

	/*정보 초기화*/
	_info_proj.id = i_id;

	/*이동관련 초기화*/
	_info_proj.velocity = FVector(v2_velocity.X, v2_velocity.Y, 0.f);
	SetActorLocation(v_spawn_loc);
	SetActorRotation(FRotator(0.f, i_yaw, 0.f));
}

void ASA_Projectile::PROJMove(const float f_delta_time, const int32 i_move_speed)
{
	AddActorWorldOffset(_info_proj.velocity * i_move_speed * f_delta_time);
}

void ASA_Projectile::PROJSetPoolActive(const bool b_is_active)
{
	if (!b_is_active)
	{
		//풀에서 활성화될때의 위치변경은 다른곳에서 합니다
		SetActorLocation(FVector(0.f, 0.f, -500.f));
	}
}

const FInfoProjectile& ASA_Projectile::GetInfoPROJ() const { return _info_proj; }