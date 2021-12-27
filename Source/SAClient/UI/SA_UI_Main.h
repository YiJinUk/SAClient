// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "UI/SA_UI_Master.h"
#include "SA_UI_Main.generated.h"

class USA_UI_Game;
class USA_UI_Title;
class ASA_PC;
class UWidgetSwitcher;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_UI_Main : public USA_UI_Master
{
	GENERATED_BODY()
	
public:
	void UIMainInit();
private:
	UPROPERTY(Meta = (BindWidget))
		UWidgetSwitcher* _switcher = nullptr;
	UPROPERTY(Meta = (BindWidget))
		USA_UI_Game* _game = nullptr;
	UPROPERTY(Meta = (BindWidget))
		USA_UI_Title* _title = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _gold = nullptr;

	UPROPERTY()
		EUIMainStatus _main_status = EUIMainStatus::TITLE;

	UPROPERTY()
		ASA_PC* _pc = nullptr;
public:
	void UIMainWaveStart();
	void UIMainWaveGameOver();
	void UIMainRetunTitle();

	void UIPlayerUpdateCheck(const FInfoPlayerCharacter& s_info_player_new, FInfoPlayerCharacter& s_info_player_old);
private:
	void UISwitchMainWidget(const EUIMainStatus e_ui_main_status);



public:
	void UIMainUpdatePlayerGold(const int32 i_gold_update);
	void UIMainUpdatePlayerDMG(const int32 i_dmg_update);
	void UIMainUpdatePlayerAS(const int32 i_as_update);
	void UIMainUpdatePlayerShotNum(const int8 i_shot_num_update);
	void UIMainUpdatePlayerPenetrate(const int8 i_penetrate_update);
};
