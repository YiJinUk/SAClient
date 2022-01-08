// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/SA_Manager_SaveLoad.h"
#include "Logic/SaveLoad/SA_SG_Game.h"
#include "Logic/SaveLoad/SA_SG_Option.h"
#include "Logic/SA_GI.h"

#include "Kismet/GameplayStatics.h"

void ASA_Manager_SaveLoad::SaveStart(const FInfoPlayer& s_info_player, const int32 i_wave_round)
{
	USA_SG_Game* save_file = Cast<USA_SG_Game>(UGameplayStatics::CreateSaveGameObject(USA_SG_Game::StaticClass()));
	if (!save_file) return;

	save_file->SGSaveData(s_info_player, i_wave_round);

	UGameplayStatics::SaveGameToSlot(save_file, "SG_Game", 0);
}
void ASA_Manager_SaveLoad::SaveOptionStart(const FInfoOption& s_info_option)
{
	USA_SG_Option* save_file = Cast<USA_SG_Option>(UGameplayStatics::CreateSaveGameObject(USA_SG_Option::StaticClass()));
	if (!save_file) return;

	save_file->SGSaveData(s_info_option);

	UGameplayStatics::SaveGameToSlot(save_file, "SG_Option", 0);
}

void ASA_Manager_SaveLoad::ReadStart(FInfoPlayer& s_info_player, int32& i_wave_round, FInfoOption& s_info_option)
{
	USA_SG_Game* save_file_game = Cast<USA_SG_Game>(UGameplayStatics::LoadGameFromSlot("SG_Game", 0));
	USA_SG_Option* save_file_option = Cast<USA_SG_Option>(UGameplayStatics::LoadGameFromSlot("SG_Option", 0));
	if (save_file_game)
	{
		s_info_player.SetGold(save_file_game->gold);
		s_info_player.SetGem(save_file_game->gem);

		s_info_player.SetDMG(save_file_game->dmg);
		s_info_player.SetAS(save_file_game->as);
		s_info_player.SetShotNumber(save_file_game->shot_num);
		s_info_player.SetPenetrate(save_file_game->penetrate);

		s_info_player.SetUpgradeCostDMG1(save_file_game->cost_dmg_1);
		s_info_player.SetUpgradeCostDMG10(save_file_game->cost_dmg_10);
		s_info_player.SetUpgradeCostAS(save_file_game->cost_as);
		s_info_player.SetUpgradeCostShotNumber(save_file_game->cost_shot_num);
		s_info_player.SetUpgradeCostPenetrate(save_file_game->cost_penetrate);

		i_wave_round = save_file_game->wave_round;
	}
	else
	{
		/*세이브데이터를 불러오지 못했습니다 기본값으로 변경합니다*/
		USA_GI* sagi = GetWorld()->GetGameInstance<USA_GI>();
		const FDataGame* s_data_game = sagi->GetDataGame();

		s_info_player.SetGold(10);
		s_info_player.SetGem(5);

		s_info_player.SetDMG(s_data_game->GetPlayerBaseDMG());
		s_info_player.SetAS(s_data_game->GetPlayerBaseAS());
		s_info_player.SetShotNumber(s_data_game->GetPlayerBaseShotNum());
		s_info_player.SetPenetrate(s_data_game->GetPlayerBasePenetrate());

		s_info_player.SetUpgradeCostDMG1(s_data_game->GetUpgradeCostDMG1());
		s_info_player.SetUpgradeCostDMG10(s_data_game->GetUpgradeCostDMG10());
		s_info_player.SetUpgradeCostAS(s_data_game->GetUpgradeCostAS());
		s_info_player.SetUpgradeCostShotNumber(s_data_game->GetUpgradeCostShotNum());
		s_info_player.SetUpgradeCostPenetrate(s_data_game->GetUpgradeCostPenetrate());

		i_wave_round = 1;
	}

	if (save_file_option)
	{
		s_info_option.is_sfx_on = save_file_option->is_sfx_on;
	}
	else
	{
		s_info_option.is_sfx_on = true;
	}
}