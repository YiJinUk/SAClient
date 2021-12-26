// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SA_UI_Main.h"
#include "Logic/SA_PC.h"
#include "Game/SA_UI_Game.h"
#include "Title/SA_UI_Title.h"

#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"

void USA_UI_Main::UIMainInit()
{
	_pc = Cast<ASA_PC>(GetOwningPlayer());
	UISwitchMainWidget(EUIMainStatus::TITLE);
	_game->UIGameInit(_pc);
	_title->UITitleInit(_pc);
}

void USA_UI_Main::UIMainRetunTitle()
{
	UISwitchMainWidget(EUIMainStatus::TITLE);
}

void USA_UI_Main::UIMainWaveStart()
{
	UISwitchMainWidget(EUIMainStatus::GAME);
}

void USA_UI_Main::UIMainWaveGameOver()
{
	_game->UIGameSetVisibleGameOver(ESlateVisibility::Visible);
}

void USA_UI_Main::UIPlayerUpdateCheck(const FInfoPlayerCharacter& s_info_player_new, FInfoPlayerCharacter& s_info_player_old)
{
	if (s_info_player_new.hp != s_info_player_old.hp)
	{
		_game->SetHP(s_info_player_new.hp);
		s_info_player_old.hp = s_info_player_new.hp;
	}
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

void USA_UI_Main::UIMainUpdatePlayerGold(const int32 i_gold_update)
{
	_gold->SetText(FText::AsNumber(i_gold_update));
}