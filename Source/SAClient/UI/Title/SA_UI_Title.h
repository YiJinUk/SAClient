// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SA_UI_Master.h"
#include "SA_UI_Title.generated.h"

class USA_GI;
class ASA_PC;
class ASA_GM;
class UButton;
class UTextBlock;
class UWidgetSwitcher;

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_UI_Title : public USA_UI_Master
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
public:
	void UITitleInit(ASA_PC* pc);
private:
	UPROPERTY(Meta = (BindWidget))
		UButton* _wave_start = nullptr;

	UPROPERTY(Meta = (BindWidget))
		UButton* _dmg_upgrade_cost1_btn = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _dmg_upgrade = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UButton* _as_upgrade_btn = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _as_upgrade = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UButton* _shot_num_upgrade_btn = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _shot_num_upgrade = nullptr;
	//UPROPERTY(Meta = (BindWidget))
	//	UButton* _penetrate_upgrade_btn = nullptr;
	//UPROPERTY(Meta = (BindWidget))
	//	UTextBlock* _penetrate_upgrade = nullptr;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _cost_dmg_1 = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _cost_as = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _cost_shot_num = nullptr;
	//UPROPERTY(Meta = (BindWidget))
	//	UTextBlock* _cost_penetrate = nullptr;

	UPROPERTY(Meta = (BindWidget))
		UWidgetSwitcher* _switcher_as = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UWidgetSwitcher* _switcher_shot_num = nullptr;

	UPROPERTY()
		USA_GI* _sagi = nullptr;
	UPROPERTY()
		ASA_PC* _pc = nullptr;
	UPROPERTY()
		ASA_GM* _gm = nullptr;
public:
	void UITitleUpdateButtons();

	void UITitleUpdatePlayerDMG(const int32 i_dmg_update);
	void UITitleUpdatePlayerAS(const int32 i_as_update);
	void UITitleUpdatePlayerShotNum(const int8 i_shot_num_update);
	void UITitleUpdatePlayerPenetrate(const int8 i_penetrate);

	void UITitleUpdateUpgradeCostDMG1(const int32 i_upgrade_cost_dmg_1);
	void UITitleUpdateUpgradeCostDMG10(const int32 i_upgrade_cost_dmg_10);
	void UITitleUpdateUpgradeCostAS(const int32 i_upgrade_cost_as);
	void UITitleUpdateUpgradeCostShotNum(const int32 i_upgrade_cost_shot_num);
	void UITitleUpdateUpgradeCostPenetrate(const int32 i_upgrade_cost_penetrate);

	UFUNCTION()
		void ClickedUpgradeDMGCost1();
	UFUNCTION()
		void ClickedUpgradeAS();
	UFUNCTION()
		void ClickedUpgradeShotNum();
	//UFUNCTION()
	//	void ClickedUpgradePenetrate();
};
