// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "GameFramework/SaveGame.h"
#include "SA_SG_Game.generated.h"

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_SG_Game : public USaveGame
{
	GENERATED_BODY()
	
public:
	void SGSaveData(const FInfoPlayer& s_info_player, const FInfoWave& s_info_wave);

public:
	UPROPERTY()
		int32 gem = 0;

	UPROPERTY()
		int32 dmg = 0;
	UPROPERTY()
		int32 as = 0;
	UPROPERTY()
		int8 shot_num = 0;
	UPROPERTY()
		int8 penetrate = 0;

	UPROPERTY()
		int32 cost_dmg_1 = 0;
	UPROPERTY()
		int32 cost_as = 0;
	UPROPERTY()
		int32 cost_shot_num = 0;
	UPROPERTY()
		int8 cost_penetrate = 0;

	UPROPERTY()
		int32 wave_round = 1;
	UPROPERTY()
		int32 wave_monster_spawn_count_max = 0;
	UPROPERTY()
		int32 monster_hp = 0;
	UPROPERTY()
		int32 monster_split_hp = 0;
};
