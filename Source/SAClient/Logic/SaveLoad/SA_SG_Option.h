// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "GameFramework/SaveGame.h"
#include "SA_SG_Option.generated.h"

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_SG_Option : public USaveGame
{
	GENERATED_BODY()

public:
	void SGSaveData(const FInfoOption& s_info_option);
public:
	UPROPERTY()
		bool is_sfx_on = false;
};
