// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "Logic/Manager/SA_Manager_Master.h"
#include "SA_Manager_SaveLoad.generated.h"

/**
 * 
 */
UCLASS()
class SACLIENT_API ASA_Manager_SaveLoad : public ASA_Manager_Master
{
	GENERATED_BODY()
	
public:
	void SaveStart(const FInfoPlayer& s_info_player, const FInfoWave& s_info_wave);
	void SaveOptionStart(const FInfoOption& s_info_option);

	void ReadStart(FInfoPlayer& s_info_player, FInfoWave& s_info_wave, FInfoOption& s_info_option);
};
