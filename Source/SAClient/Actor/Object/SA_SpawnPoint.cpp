// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/SA_SpawnPoint.h"
#include "Logic/SA_FunctionLibrary.h"



void ASA_SpawnPoint::SpawnPointInit(const FVector& v_dest)
{
	//Get velocity
	_velocity = USA_FunctionLibrary::GetVelocityByV3(GetActorLocation(), v_dest);

	//Get rotator
	_rot.Yaw = USA_FunctionLibrary::GetLookRotatorYawByV3(GetActorLocation(), v_dest);

	_spawn_loc = FVector(GetActorLocation().X, GetActorLocation().Y, 0.f);
}

const FRotator& ASA_SpawnPoint::GetPointRotator() const { return _rot; }
const FVector& ASA_SpawnPoint::GetPointVelocity() const { return _velocity; }
const FVector& ASA_SpawnPoint::GetPointSpawnLocation() const { return _spawn_loc; }
