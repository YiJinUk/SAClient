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
	//������ �� �ѹ��� ȣ���մϴ�. Ǯ������ ȣ����� �ʽ��ϴ�
	void MOBPostInit(const FString& str_code_monster);
	//Ǯ���� ���� �� ���� ȣ��˴ϴ�
	void MOBInit(const int64 i_id, const FVector& v_spawn_loc, const FVector& v_velocity, const FRotator& r_rot);
	void MOBMove(const float f_delta_time);

	FORCEINLINE const FInfoMonster& GetInfoMonster() const;
protected:
	UPROPERTY()
		FInfoMonster _info_monster;
};
