// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "Logic/Manager/SA_Manager_Master.h"
#include "SA_Manager_VFX.generated.h"

class USA_GI;

/**
 * 
 */
UCLASS()
class SACLIENT_API ASA_Manager_VFX : public ASA_Manager_Master
{
	GENERATED_BODY()
public:
	void VFXInit(USA_GI* sagi);
private:
	FDataVFX* _data_vfx_cache = nullptr;
public:
	void VFXStart(const EVFXType e_vfx_type, const FVector& v_loc);
};
