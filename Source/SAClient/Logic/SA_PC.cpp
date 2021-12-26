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

void ASA_PC::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Tap", IE_Pressed, this, &ASA_PC::TapPressed);
}

void ASA_PC::TapPressed()
{
	/*
	* 발사체를 발사합니다
	* 시작점 : 플레이어 캐릭터
	* 도착점 : 탭 위치
	* Z값 : 고정
	* 
	* 탭 위치는 바닥의 위치를 통해 알 수 있습니다
	*/
	//USA_FunctionLibrary::GPrintString(100, 2, "TapPressed");
	/*탭 위치 가져오기 ECC_GameTraceChannel3=PLANE*/
	GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, _tap_hit);
	_sagm->ShootPROJ(_tap_hit.Location);
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