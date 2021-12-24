// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/SA_PC.h"
#include "SA_GM.h"
#include "UI/Game/SA_UI_Game.h"


void ASA_PC::PCInit(ASA_GM* sagm, FInfoPlayer& s_info_player)
{
	_sagm = sagm;
	_ui_info_player = s_info_player;
	//�������Ʈ���� �ʱ�ȭ�ؾ��ϴ°��� �ʱ�ȭ�մϴ�
	PCBPInit();

	//������ �����մϴ�
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