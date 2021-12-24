// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "Actor/Unit/SA_Unit.h"
#include "SA_Monster.generated.h"

/**
 * 
 */
UCLASS()
class SACLIENT_API ASA_Monster : public ASA_Unit
{
	GENERATED_BODY()
	
public:
	//생성시 딱 한번만 호출합니다. 풀링에서 호출되지 않습니다
	void MOBPostInit(const FString& str_code_monster);
	//풀에서 나올 때 마다 호출됩니다
	void MOBInit(const int64 i_id, const FVector& v_spawn_loc, const FVector& v_velocity, const FRotator& r_rot);
	void MOBMove(const float f_delta_time);

	FORCEINLINE const FInfoMonster& GetInfoMonster() const;
protected:
	UPROPERTY()
		FInfoMonster _info_monster;
};
