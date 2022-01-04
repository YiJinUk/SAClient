// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/SA_Manager_VFX.h"
#include "Logic/SA_GI.h"

#include "Kismet/GameplayStatics.h"

void ASA_Manager_VFX::VFXInit(USA_GI* sagi)
{
	_data_vfx_cache = sagi->FindDataVFXByCode("VFX00001");
}

void ASA_Manager_VFX::VFXStart(const EVFXType e_vfx_type, const FVector& v_loc)
{
	switch (e_vfx_type)
	{
	case EVFXType::PROJ_HIT:
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), _data_vfx_cache->GetPROJHit(), v_loc);
		break;
	default:
		break;
	}
}