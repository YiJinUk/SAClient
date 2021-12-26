// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "Actor/Unit/SA_Unit.h"
#include "SA_Monster.generated.h"

class USA_UI_Headup_Monster;

/**
 * 
 */
UCLASS()
class SACLIENT_API ASA_Monster : public ASA_Unit
{
	GENERATED_BODY()
	
protected:
	ASA_Monster(FObjectInitializer const& object_initializer);

public:
	//������ �� �ѹ��� ȣ���մϴ�. Ǯ������ ȣ����� �ʽ��ϴ�
	void MOBPostInit(const FDataMonster* s_data_monster);
	//Ǯ���� ���� �� ���� ȣ��˴ϴ�
	void MOBInit(const int64 i_id, const FVector& v_spawn_loc, const FVector& v_velocity, const FRotator& r_rot);
	void MOBMove(const float f_delta_time);

	void MOBSetPooling(const bool b_is_active);

	FORCEINLINE const FInfoMonster& GetInfoMonster() const;

protected:
	UPROPERTY(EditAnywhere)
		class UWidgetComponent* _ui_headup = nullptr;
	UPROPERTY()
		USA_UI_Headup_Monster* _ui_headup_monster = nullptr;

	UPROPERTY()
		FInfoMonster _info_monster;
};
