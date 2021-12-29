// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/SA_PC.h"
#include "Logic/SA_FunctionLibrary.h"
#include "SA_GM.h"
#include "UI/SA_UI_Main.h"

ASA_PC::ASA_PC()
{
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
}

void ASA_PC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (_is_tap_pressed && _sagm)
	{
		GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, _tap_hit);
		_sagm->ChangePROJVelocity(_tap_hit.Location);
	}
}

void ASA_PC::PCInit(ASA_GM* sagm, FInfoPlayerCharacter& s_info_player_chr)
{
	_sagm = sagm;
	//_ui_info_player_chr = s_info_player_chr;
	const FInfoPlayer& s_info_player = _sagm->GetInfoPlayer();
	_ui_info_player = s_info_player;
	//�������Ʈ���� �ʱ�ȭ�ؾ��ϴ°��� �ʱ�ȭ�մϴ�
	PCBPInit();

	//������ ���� �� �ʱ�ȭ�մϴ�
	_ui_main = PCCreateWidgetMain();
	_ui_main->UIMainInit();
	PCUIUpdateCheck();

	/*������ ���������� �ʱ�ȭ�մϴ�*/
	PCUIUpdatePlayerStat(EPlayerStat::GOLD, _ui_info_player.GetGold());
	PCUIUpdatePlayerStat(EPlayerStat::DMG, _ui_info_player.GetDMG());
	PCUIUpdatePlayerStat(EPlayerStat::AS, _ui_info_player.GetAS());
	PCUIUpdatePlayerStat(EPlayerStat::SHOT_NUMBER, _ui_info_player.GetShotNumber());
	PCUIUpdatePlayerStat(EPlayerStat::PENETRATE, _ui_info_player.GetPenetrate());
	PCUIUpdateWaveRound(_sagm->GetWaveRoundCurrent());
}

void ASA_PC::PCWaveStart()
{
	_ui_main->UIMainWaveStart();
}

void ASA_PC::PCWaveClear(const int32 i_wave_round)
{
	_ui_main->UIMainWaveClear();
	PCUIUpdateWaveRound(i_wave_round);
}

void ASA_PC::PCWaveGameOver()
{
	_ui_main->UIMainWaveGameOver();
}

void ASA_PC::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Tap", IE_Pressed, this, &ASA_PC::TapPressed);
	InputComponent->BindAction("Tap", IE_Released, this, &ASA_PC::TapReleased);
}

void ASA_PC::TapPressed()
{
	_is_tap_pressed = true;
}

void ASA_PC::TapReleased()
{
	_is_tap_pressed = false;
}

void ASA_PC::PCUIUpdateCheck()
{
	const FInfoPlayerCharacter& s_info_player_chr = _sagm->GetInfoPlayerChr();
	_ui_main->UIPlayerUpdateCheck(s_info_player_chr, _ui_info_player_chr);

	//_ui_info_player_chr = s_info_player_chr;
}
void ASA_PC::PCReturnTitle()
{
	_sagm->ReturnTitle();
	_ui_main->UIMainRetunTitle();
}

void ASA_PC::PCUIUpdatePlayerStat(const EPlayerStat e_player_stat, const int32 i_value)
{
	switch (e_player_stat)
	{
	case EPlayerStat::GOLD:
		_ui_info_player.SetGold(i_value);
		_ui_main->UIMainUpdatePlayerGold(_ui_info_player.GetGold());
		break;
	case EPlayerStat::DMG:
		_ui_info_player.SetDMG(i_value);
		_ui_main->UIMainUpdatePlayerDMG(_ui_info_player.GetDMG());
		break;
	case EPlayerStat::AS:
		_ui_info_player.SetAS(i_value);
		_ui_main->UIMainUpdatePlayerAS(_ui_info_player.GetAS());
		break;
	case EPlayerStat::SHOT_NUMBER:
		_ui_info_player.SetShotNumber(i_value);
		_ui_main->UIMainUpdatePlayerShotNum(_ui_info_player.GetShotNumber());
		break;
	case EPlayerStat::PENETRATE:
		_ui_info_player.SetPenetrate(i_value);
		_ui_main->UIMainUpdatePlayerPenetrate(_ui_info_player.GetPenetrate());
		break;
	default:
		break;
	}
}

void ASA_PC::PCUIUpdateWaveRound(const int32 i_wave_round)
{
	_ui_main->UIMainUpdateWaveRound(i_wave_round);
}