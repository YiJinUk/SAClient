// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/SA_Manager_SaveLoad.h"
#include "Logic/SA_SG.h"
#include "Logic/SA_GI.h"

#include "Kismet/GameplayStatics.h"

void ASA_Manager_SaveLoad::SaveStart(const FInfoPlayer& s_info_player)
{
	USA_SG* save_file = Cast<USA_SG>(UGameplayStatics::CreateSaveGameObject(USA_SG::StaticClass()));
	if (!save_file) return;

	save_file->SGSaveData(s_info_player);

	UGameplayStatics::SaveGameToSlot(save_file, "SASave", 0);
}

void ASA_Manager_SaveLoad::ReadStart(FInfoPlayer& s_info_player)
{
	USA_SG* save_file = Cast<USA_SG>(UGameplayStatics::LoadGameFromSlot("SASave", 0));
	if (save_file)
	{
		s_info_player.SetGold(save_file->gold);
		s_info_player.SetDMG(save_file->dmg);
		s_info_player.SetAS(save_file->as);
		s_info_player.SetShotNumber(save_file->shot_num);
		s_info_player.SetPenetrate(save_file->penetrate);
	}
	else
	{
		/*세이브데이터를 불러오지 못했습니다 기본값으로 변경합니다*/
		USA_GI* sagi = GetWorld()->GetGameInstance<USA_GI>();
		const FDataGame* s_data_game = sagi->GetDataGame();

		s_info_player.SetGold(10);
		s_info_player.SetDMG(s_data_game->GetPlayerBaseDMG());
		s_info_player.SetAS(s_data_game->GetPlayerBaseAS());
		s_info_player.SetShotNumber(s_data_game->GetPlayerBaseShotNum());
		s_info_player.SetPenetrate(s_data_game->GetPlayerBasePenetrate());
	}
}