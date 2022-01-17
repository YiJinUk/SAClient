// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/SA_PC.h"
#include "Logic/SA_FunctionLibrary.h"
#include "SA_GM.h"
#include "UI/SA_UI_Main.h"
#include "UI/Game/SA_UI_Obtain_Gem.h"

#include "Kismet/KismetInternationalizationLibrary.h"
#include "Kismet/GameplayStatics.h"

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

void ASA_PC::DebugRefreshTitle()
{
	const FInfoPlayer& s_info_player = _sagm->GetInfoPlayer();
	_ui_info_player = s_info_player;

	/*위젯을 세부적으로 초기화합니다*/
	PCUIUpdatePlayerStat(EPlayerStat::GEM, _ui_info_player.GetGem());
	PCUIUpdatePlayerStat(EPlayerStat::DMG, _ui_info_player.GetDMG());
	PCUIUpdatePlayerStat(EPlayerStat::AS, _ui_info_player.GetAS());
	PCUIUpdatePlayerStat(EPlayerStat::SHOT_NUMBER, _ui_info_player.GetShotNumber());
	PCUIUpdatePlayerStat(EPlayerStat::PENETRATE, _ui_info_player.GetPenetrate());

	PCUIUpdateUpgradeCost(EUpgradeStat::DMG, _ui_info_player.GetUpgradeCostDMG());
	PCUIUpdateUpgradeCost(EUpgradeStat::AS, _ui_info_player.GetUpgradeCostAS());
	PCUIUpdateUpgradeCost(EUpgradeStat::SHOT_NUMBER, _ui_info_player.GetUpgradeCostShotNumber());
	PCUIUpdateUpgradeCost(EUpgradeStat::PENETRATE, _ui_info_player.GetUpgradeCostPenetrate());

	PCUIUpdateWaveRound(_sagm->GetWaveRoundCurrent());
}

void ASA_PC::PCInit(ASA_GM* sagm, FInfoPlayerCharacter& s_info_player_chr)
{
	_sagm = sagm;
	//_ui_info_player_chr = s_info_player_chr;
	const FInfoPlayer& s_info_player = _sagm->GetInfoPlayer();
	_ui_info_player = s_info_player;
	//블루프린트에서 초기화해야하는것은 초기화합니다
	PCBPInit();

	//위젯을 생성 및 초기화합니다
	_ui_main = PCCreateWidgetMain();
	_ui_main->UIMainInit();
	PCUIUpdateCheck();

	/*위젯을 세부적으로 초기화합니다*/
	PCUIUpdatePlayerStat(EPlayerStat::GEM, _ui_info_player.GetGem());
	PCUIUpdatePlayerStat(EPlayerStat::DMG, _ui_info_player.GetDMG());
	PCUIUpdatePlayerStat(EPlayerStat::AS, _ui_info_player.GetAS());
	PCUIUpdatePlayerStat(EPlayerStat::SHOT_NUMBER, _ui_info_player.GetShotNumber());
	PCUIUpdatePlayerStat(EPlayerStat::PENETRATE, _ui_info_player.GetPenetrate());

	PCUIUpdateUpgradeCost(EUpgradeStat::DMG, _ui_info_player.GetUpgradeCostDMG());
	PCUIUpdateUpgradeCost(EUpgradeStat::AS, _ui_info_player.GetUpgradeCostAS());
	PCUIUpdateUpgradeCost(EUpgradeStat::SHOT_NUMBER, _ui_info_player.GetUpgradeCostShotNumber());
	PCUIUpdateUpgradeCost(EUpgradeStat::PENETRATE, _ui_info_player.GetUpgradeCostPenetrate());

	PCUIUpdateWaveRound(_sagm->GetWaveRoundCurrent());
}

void ASA_PC::PCWaveStart()
{
	_ui_main->UIMainWaveStart();
}

void ASA_PC::PCWaveClear(const FInfoWaveClear& s_info_wave_clear)
{
	_ui_main->UIMainWaveClear(s_info_wave_clear);
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
void ASA_PC::PCUISetCheckBoxSFX(const bool b_is_checked)
{
	_ui_main->UIMainSetCheckBoxSFX(b_is_checked);
}
void ASA_PC::PCUISetLanguageBtn(const bool b_is_ko)
{
	_ui_main->UIMainSetLanguageBtn(b_is_ko);
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
	case EPlayerStat::GEM:
		_ui_info_player.SetGem(i_value);
		_ui_main->UIMainUpdatePlayerGem(_ui_info_player.GetGem());
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

void ASA_PC::PCUIUpdateUpgradeCost(const EUpgradeStat e_upgrade_cost, const int32 i_value)
{
	switch (e_upgrade_cost)
	{
	case EUpgradeStat::DMG:
		_ui_info_player.SetUpgradeCostDMG(i_value);
		_ui_main->UIMainUpdateUgradeCostDMG1(i_value);
		break;
	case EUpgradeStat::AS:
		_ui_info_player.SetUpgradeCostAS(i_value);
		_ui_main->UIMainUpdateUgradeCostAS(i_value);
		break;
	case EUpgradeStat::SHOT_NUMBER:
		_ui_info_player.SetUpgradeCostShotNumber(i_value);
		_ui_main->UIMainUpdateUgradeCostShotNum(i_value);
		break;
	case EUpgradeStat::PENETRATE:
		_ui_info_player.SetUpgradeCostPenetrate(i_value);
		_ui_main->UIMainUpdateUgradeCostPenetrate(i_value);
		break;
	default:
		break;
	}
}

void ASA_PC::PCUIUpdateWaveRound(const int32 i_wave_round)
{
	_ui_main->UIMainUpdateWaveRound(i_wave_round);
}

void ASA_PC::PCKillMonster(const FVector& v_loc_monster, const int32 i_obtain_gem)
{
	USA_UI_Obtain_Gem* ui_obtain_gem = PoolOutUIObtainGem();
	if (!ui_obtain_gem) return;

	FVector2D v_loc_floating;
	UGameplayStatics::ProjectWorldToScreen(this, v_loc_monster, v_loc_floating);
	//v_loc_floating += _plgi->GetDataGame()->GetFloatingDmgNumberOffset();

	ui_obtain_gem->AddToViewport();
	ui_obtain_gem->SetPositionInViewport(v_loc_floating);
	ui_obtain_gem->SetRenderTransformPivot(FVector2D(0.5f, 0.5f));
	ui_obtain_gem->PlayAnim(i_obtain_gem);
}

USA_UI_Obtain_Gem* ASA_PC::PoolOutUIObtainGem()
{
	if (_obtain_gems.Num() <= 0)
	{
		return CreateWidgetObtainGem();
	}
	else
	{
		return _obtain_gems.Pop();
	}
}
void ASA_PC::PoolInUIObtainGem(USA_UI_Obtain_Gem* obtain_gem)
{
	_obtain_gems.Add(obtain_gem);
}

const FInfoPlayer& ASA_PC::GetUIInfoPlayer() const { return _ui_info_player; }