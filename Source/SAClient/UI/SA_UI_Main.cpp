// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SA_UI_Main.h"
#include "Logic/SA_PC.h"
#include "Game/SA_UI_Game.h"
#include "Title/SA_UI_Title.h"
#include "SA_UI_Option.h"

#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void USA_UI_Main::NativeConstruct()
{
	Super::NativeConstruct();
	_option_show->OnClicked.AddDynamic(this, &USA_UI_Main::ClickedOptionShow);
}

void USA_UI_Main::UIMainInit()
{
	_pc = Cast<ASA_PC>(GetOwningPlayer());
	UISwitchMainWidget(EUIMainStatus::TITLE);
	_game->UIGameInit(_pc);
	_title->UITitleInit(_pc);
	_option->SetVisibility(ESlateVisibility::Hidden);
}

void USA_UI_Main::UIMainRetunTitle()
{
	_game->UIGameSetVisibleWaveClear(ESlateVisibility::Hidden);
	UISwitchMainWidget(EUIMainStatus::TITLE);
}

void USA_UI_Main::UIMainWaveStart()
{
	UISwitchMainWidget(EUIMainStatus::GAME);
}
void USA_UI_Main::UIMainWaveClear(const FInfoWaveClear& s_info_wave_clear)
{
	_game->UIGameWaveClear(s_info_wave_clear);
	_title->UITitleUpdateButtons();
}
void USA_UI_Main::UIMainWaveGameOver()
{
	_game->UIGameWaveGameOver();
	_title->UITitleUpdateButtons();
}

void USA_UI_Main::UIPlayerUpdateCheck(const FInfoPlayerCharacter& s_info_player_new, FInfoPlayerCharacter& s_info_player_old)
{
	if (s_info_player_new.hp != s_info_player_old.hp)
	{
		_game->SetHP(s_info_player_new.hp);
		s_info_player_old.hp = s_info_player_new.hp;
	}
}
void USA_UI_Main::UIMainSetCheckBoxSFX(const bool b_is_checked)
{
	_option->UIOptionSetCheckBoxSFX(b_is_checked);
}
void USA_UI_Main::UIMainSetLanguageBtn(const bool b_is_ko)
{
	_option->UIOptionSetLanguageBtn(b_is_ko);
}
void USA_UI_Main::UIMainUpdateWaveRound(const int32 i_wave_current)
{
	_wave_round->SetText(FText::AsNumber(i_wave_current));
}

void USA_UI_Main::UISwitchMainWidget(const EUIMainStatus e_ui_main_status)
{
	_main_status = e_ui_main_status;
	switch (_main_status)
	{
	case EUIMainStatus::TITLE:
		_switcher->SetActiveWidgetIndex(0);
		break;
	case EUIMainStatus::GAME:
		_switcher->SetActiveWidgetIndex(1);
		break;
	default:
		break;
	}
}
void USA_UI_Main::ClickedOptionShow()
{
	_pc->SetPause(true);
	_option->SetVisibility(ESlateVisibility::Visible);
}

void USA_UI_Main::UIMainUpdatePlayerGem(const int32 i_gem_update)
{
	_gem->SetText(FText::AsNumber(i_gem_update));
}
void USA_UI_Main::UIMainUpdatePlayerDMG(const int32 i_dmg_update)
{
	_title->UITitleUpdatePlayerDMG(i_dmg_update);
	_game->UIGameUpdatePlayerDMG(i_dmg_update);
}
void USA_UI_Main::UIMainUpdatePlayerAS(const int32 i_as_update)
{
	_title->UITitleUpdatePlayerAS(i_as_update);
	_game->UIGameUpdatePlayerAS(i_as_update);
}
void USA_UI_Main::UIMainUpdatePlayerShotNum(const int8 i_shot_num_update)
{
	_title->UITitleUpdatePlayerShotNum(i_shot_num_update);
}
void USA_UI_Main::UIMainUpdatePlayerPenetrate(const int8 i_penetrate_update)
{
	_title->UITitleUpdatePlayerPenetrate(i_penetrate_update);
}
void USA_UI_Main::UIMainUpdateUgradeCostDMG1(const int32 i_upgrade_cost_dmg_1)
{
	_title->UITitleUpdateUpgradeCostDMG1(i_upgrade_cost_dmg_1);
}
void USA_UI_Main::UIMainUpdateUgradeCostAS(const int32 i_upgrade_cost_as)
{
	_title->UITitleUpdateUpgradeCostAS(i_upgrade_cost_as);
}
void USA_UI_Main::UIMainUpdateUgradeCostShotNum(const int32 i_upgrade_cost_shot_num)
{
	_title->UITitleUpdateUpgradeCostShotNum(i_upgrade_cost_shot_num);
}
void USA_UI_Main::UIMainUpdateUgradeCostPenetrate(const int32 i_upgrade_cost_penetrate)
{
	_title->UITitleUpdateUpgradeCostPenetrate(i_upgrade_cost_penetrate);
}