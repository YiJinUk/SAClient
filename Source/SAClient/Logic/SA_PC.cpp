// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/SA_PC.h"
#include "SA_GM.h"
#include "UI/Game/SA_UI_Game.h"


void ASA_PC::PCInit(ASA_GM* sagm, FInfoPlayer& s_info_player)
{
	_sagm = sagm;
	_ui_info_player = s_info_player;
	//블루프린트에서 초기화해야하는것은 초기화합니다
	PCBPInit();

	//위젯을 생성합니다
	_ui_game = PCCreateWidgetGame();
	_ui_title = PCCreateWidgetTitle();
	_ui_game->SetVisibility(ESlateVisibility::Hidden);
	//_ui_title->SetVisibility(ESlateVisibility::Visible);

}

void ASA_PC::PCUIUpdateCheck()
{
	const FInfoPlayer& s_info_player = _sagm->GetInfoPlayer();
	_ui_game->UIPlayerUpdateCheck(s_info_player, _ui_info_player);

	_ui_info_player = s_info_player;
}