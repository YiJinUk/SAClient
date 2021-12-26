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
	//��������Ʈ���� �ʱ�ȭ�ؾ��ϴ°��� �ʱ�ȭ�մϴ�
	PCBPInit();

	//������ ���� �� �ʱ�ȭ�մϴ�
	_ui_main = PCCreateWidgetMain();
	_ui_main->UIMainInit();
	PCUIUpdateCheck();

	/*������ ���������� �ʱ�ȭ�մϴ�*/
	PCUIUpdatePlayerGold(_ui_info_player.GetGold());
	PCUIUpdatePlayerDMG(_ui_info_player.GetDMG());
}

void ASA_PC::PCWaveStart()
{
	_ui_main->UIMainWaveStart();
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

void ASA_PC::PCUIUpdatePlayerGold(const int32 i_gold_update)
{
	_ui_info_player.SetGold(i_gold_update);
	_ui_main->UIMainUpdatePlayerGold(_ui_info_player.GetGold());
}
void ASA_PC::PCUIUpdatePlayerDMG(const int32 i_dmg_update)
{
	_ui_info_player.SetDMG(i_dmg_update);
	_ui_main->UIMainUpdatePlayerDMG(_ui_info_player.GetDMG());
}