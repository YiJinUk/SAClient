// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "Logic/Manager/SA_Manager_Master.h"
#include "SA_Manager_SFX.generated.h"

class USA_GI;

/**
 * 
 */
UCLASS()
class SACLIENT_API ASA_Manager_SFX : public ASA_Manager_Master
{
	GENERATED_BODY()
public:
	void SFXInit(USA_GI* sagi);
private:
	FDataSFX* _data_sfx_cache = nullptr;
public:
	void SFXStart(const ESFXType e_sfx_type);
};
