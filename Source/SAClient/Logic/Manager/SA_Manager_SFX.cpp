// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/SA_Manager_SFX.h"
#include "Logic/SA_GI.h"

#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

void ASA_Manager_SFX::SFXInit(USA_GI* sagi)
{
	_data_sfx_cache = sagi->FindDataSFXByCode("SFX00001");
}

void ASA_Manager_SFX::SFXStart(const ESFXType e_sfx_type)
{
	switch (e_sfx_type)
	{
	case ESFXType::BACKGROUND:
		UGameplayStatics::SpawnSound2D(GetWorld(), _data_sfx_cache->GetBackGround())->SetUISound(true);
		break;
	case ESFXType::PROJ_SHOT:
		UGameplayStatics::SpawnSound2D(GetWorld(), _data_sfx_cache->GetPROJShot(),1.f,1.f,0.2f);
		break;
	case ESFXType::PROJ_HIT:
		UGameplayStatics::SpawnSound2D(GetWorld(), _data_sfx_cache->GetPROJHit());
		break;
	default:
		break;
	}
}