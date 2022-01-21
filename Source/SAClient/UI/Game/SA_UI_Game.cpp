// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/SA_UI_Game.h"
#include "SA_UI_GameOver.h"
#include "SA_UI_WaveClear.h"

#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void USA_UI_Game::UIGameInit(ASA_PC* pc)
{
	_ui_game_over->UIGameOverInit(pc);
	_switcher->SetActiveWidgetIndex(2);
}

void USA_UI_Game::UIGameWaveClear(const FInfoWaveClear& s_info_wave_clear)
{
	_ui_wave_clear->UIWaveClearUpdate(s_info_wave_clear);
	UIGameSetVisibleWaveClear(ESlateVisibility::SelfHitTestInvisible);
}

void USA_UI_Game::UIGameWaveGameOver()
{
	_ui_game_over->UIGameOverUpdate();
	UIGameSetVisibleGameOver(ESlateVisibility::Visible);
}

void USA_UI_Game::UIGameSetVisibleGameOver(const ESlateVisibility e_ui_visible)
{
	if (e_ui_visible == ESlateVisibility::Hidden)
	{
		_switcher->SetActiveWidgetIndex(2);
	}
	else
	{
		_switcher->SetActiveWidgetIndex(0);
	}
	
	//_ui_game_over->SetVisibility(e_ui_visible);
}
void USA_UI_Game::UIGameSetVisibleWaveClear(const ESlateVisibility e_ui_visible)
{
	if (e_ui_visible == ESlateVisibility::Hidden)
	{
		_switcher->SetActiveWidgetIndex(2);
	}
	else
	{
		_switcher->SetActiveWidgetIndex(1);
	}
	//_ui_wave_clear->SetVisibility(e_ui_visible);
}