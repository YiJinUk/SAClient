// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Unit/Monster/SA_Monster.h"
#include "SA_MOB00002.generated.h"

/**
 * 
 */
UCLASS()
class SACLIENT_API ASA_MOB00002 : public ASA_Monster
{
	GENERATED_BODY()

protected:
	void MOBPostInitChild(const FDataMonster* s_data_monster) override;
};
