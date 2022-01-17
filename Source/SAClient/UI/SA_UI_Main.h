// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "UI/SA_UI_Master.h"
#include "SA_UI_Main.generated.h"

class USA_UI_Game;
class USA_UI_Title;
class USA_UI_Option;
class ASA_PC;
class UWidgetSwitcher;
class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_UI_Main : public USA_UI_Master
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
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
		USA_UI_Option* _option = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _gem = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _wave_round = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UButton* _option_show = nullptr;

	UPROPERTY(Meta = (BindWidgetAnim), Transient, Meta = (AllowPrivateAccess = true))
		UWidgetAnimation* _get_gem = nullptr;

	UPROPERTY()
		EUIMainStatus _main_status = EUIMainStatus::TITLE;

	UPROPERTY()
		ASA_PC* _pc = nullptr;
public:
	void UIMainWaveStart();
	void UIMainWaveClear(const FInfoWaveClear& s_info_wave_clear);
	void UIMainWaveGameOver();
	void UIMainRetunTitle();

	void UIPlayerUpdateCheck(const FInfoPlayerCharacter& s_info_player_new, FInfoPlayerCharacter& s_info_player_old);
	void UIMainSetCheckBoxSFX(const bool b_is_checked);
	void UIMainSetLanguageBtn(const bool b_is_ko);
	void UIMainUpdateWaveRound(const int32 i_wave_current);
private:
	void UISwitchMainWidget(const EUIMainStatus e_ui_main_status);
	UFUNCTION()
		void ClickedOptionShow();


public:
	void UIMainUpdatePlayerGem(const int32 i_gem_update);
	void UIMainUpdatePlayerDMG(const int32 i_dmg_update);
	void UIMainUpdatePlayerAS(const int32 i_as_update);
	void UIMainUpdatePlayerShotNum(const int8 i_shot_num_update);
	void UIMainUpdatePlayerPenetrate(const int8 i_penetrate_update);

	void UIMainUpdateUgradeCostDMG1(const int32 i_upgrade_cost_dmg_1);
	void UIMainUpdateUgradeCostAS(const int32 i_upgrade_cost_as);
	void UIMainUpdateUgradeCostShotNum(const int32 i_upgrade_cost_shot_num);
	void UIMainUpdateUgradeCostPenetrate(const int32 i_upgrade_cost_penetrate);
};
