// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/SA_PC.h"
#include "SA_GM.h"
#include "UI/SA_UI_Main.h"


void ASA_PC::PCInit(ASA_GM* sagm, FInfoPlayer& s_info_player)
{
	_sagm = sagm;
	_ui_info_player = s_info_player;
	//블루프린트에서 초기화해야하는것은 초기화합니다
	PCBPInit();

	//위젯을 생성합니다
	_ui_main = PCCreateWidgetMain();
	_ui_main->UIMainInit();
}

void ASA_PC::PCWaveStart()
{
	_ui_main->UIMainWaveStart();
}

void ASA_PC::PCWaveGameOver()
{
	_ui_main->UIMainWaveGameOver();
}

void ASA_PC::PCUIUpdateCheck()
{
	const FInfoPlayer& s_info_player = _sagm->GetInfoPlayer();
	_ui_main->UIPlayerUpdateCheck(s_info_player, _ui_info_player);

	_ui_info_player = s_info_player;
}
void ASA_PC::PCReturnTitle()
{
	_sagm->ReturnTitle();
	_ui_main->UIMainRetunTitle();
}