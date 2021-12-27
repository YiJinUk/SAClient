// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "GameFramework/SaveGame.h"
#include "SA_SG.generated.h"

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_SG : public USaveGame
{
	GENERATED_BODY()
	
public:
	void SGSaveData(const FInfoPlayer& s_info_player);

public:
	UPROPERTY()
		int32 gold = 0;

	UPROPERTY()
		int32 dmg = 0;
	UPROPERTY()
		int32 as = 0;
	UPROPERTY()
		int8 shot_num = 0;
	UPROPERTY()
		int8 penetrate = 0;
};
