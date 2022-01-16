// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Title/SA_UI_Title.h"
#include "Logic/SA_GI.h"
#include "Logic/SA_PC.h"
#include "Logic/SA_GM.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void USA_UI_Title::NativeConstruct()
{
	Super::NativeConstruct();
	_dmg_upgrade_cost1_btn->OnClicked.AddDynamic(this, &USA_UI_Title::ClickedUpgradeDMGCost1);
	_as_upgrade_btn->OnClicked.AddDynamic(this, &USA_UI_Title::ClickedUpgradeAS);
	_shot_num_upgrade_btn->OnClicked.AddDynamic(this, &USA_UI_Title::ClickedUpgradeShotNum);
	//_penetrate_upgrade_btn->OnClicked.AddDynamic(this, &USA_UI_Title::ClickedUpgradePenetrate);
}
void USA_UI_Title::UITitleInit(ASA_PC* pc)
{
	_pc = pc;
	_gm = GetWorld()->GetAuthGameMode<ASA_GM>();
	_sagi = GetWorld()->GetGameInstance<USA_GI>();
	UITitleUpdateButtons();
}

void USA_UI_Title::UITitleUpdateButtons()
{
	const FInfoPlayer& s_ui_info_player = _pc->GetUIInfoPlayer();

	if (s_ui_info_player.GetUpgradeCostDMG1() <= s_ui_info_player.GetGem())
		_dmg_upgrade_cost1_btn->SetIsEnabled(true);
	else
		_dmg_upgrade_cost1_btn->SetIsEnabled(false);

	if (s_ui_info_player.GetAS() >= _sagi->GetDataGame()->GetUpgradeMaxAS())
	{
		_as_upgrade_btn->SetIsEnabled(false);
		_switcher_as->SetActiveWidgetIndex(1);
	}
	else
	{
		_switcher_as->SetActiveWidgetIndex(0);
		if (s_ui_info_player.GetUpgradeCostAS() <= s_ui_info_player.GetGem())
			_as_upgrade_btn->SetIsEnabled(true);
		else
			_as_upgrade_btn->SetIsEnabled(false);
	}
	

	if (s_ui_info_player.GetShotNumber() >= _sagi->GetDataGame()->GetUpgradeMaxShotNum())
	{
		_shot_num_upgrade_btn->SetIsEnabled(false);
		_switcher_shot_num->SetActiveWidgetIndex(1);
	}
	else
	{
		_switcher_shot_num->SetActiveWidgetIndex(0);
		if (s_ui_info_player.GetUpgradeCostShotNumber() <= s_ui_info_player.GetGem())
			_shot_num_upgrade_btn->SetIsEnabled(true);
		else
			_shot_num_upgrade_btn->SetIsEnabled(false);
	}
}

void USA_UI_Title::UITitleUpdatePlayerDMG(const int32 i_dmg_update)
{
	_dmg_upgrade->SetText(FText::AsNumber(i_dmg_update));
	UITitleUpdateButtons();
}
void USA_UI_Title::UITitleUpdatePlayerAS(const int32 i_as_update)
{
	//_as_upgrade->SetText(FText::AsNumber(60.f / (float)i_as_update * 60.f));
	_as_upgrade->SetText(FText::AsNumber(i_as_update / 60.f));
	UITitleUpdateButtons();
}
void USA_UI_Title::UITitleUpdatePlayerShotNum(const int8 i_shot_num_update)
{
	_shot_num_upgrade->SetText(FText::AsNumber(i_shot_num_update));
	UITitleUpdateButtons();
}
void USA_UI_Title::UITitleUpdatePlayerPenetrate(const int8 i_penetrate)
{
	//_penetrate_upgrade->SetText(FText::AsNumber(i_penetrate));
}
void USA_UI_Title::UITitleUpdateUpgradeCostDMG1(const int32 i_upgrade_cost_dmg_1)
{
	_cost_dmg_1->SetText(FText::AsNumber(i_upgrade_cost_dmg_1));
}
void USA_UI_Title::UITitleUpdateUpgradeCostDMG10(const int32 i_upgrade_cost_dmg_10)
{
	//_cost_dmg_10->SetText(FText::AsNumber(i_upgrade_cost_dmg_10));
}
void USA_UI_Title::UITitleUpdateUpgradeCostAS(const int32 i_upgrade_cost_as)
{
	_cost_as->SetText(FText::AsNumber(i_upgrade_cost_as));
}
void USA_UI_Title::UITitleUpdateUpgradeCostShotNum(const int32 i_upgrade_cost_shot_num)
{
	_cost_shot_num->SetText(FText::AsNumber(i_upgrade_cost_shot_num));
}
void USA_UI_Title::UITitleUpdateUpgradeCostPenetrate(const int32 i_upgrade_cost_penetrate)
{
	//_cost_penetrate->SetText(FText::AsNumber(i_upgrade_cost_penetrate));
}

void USA_UI_Title::ClickedUpgradeDMGCost1()
{
	_gm->UpgradeDMG(1);
	//UITitleUpdateButtons();
}
void USA_UI_Title::ClickedUpgradeAS()
{
	_gm->UpgradeAS();
	//UITitleUpdateButtons();
}
void USA_UI_Title::ClickedUpgradeShotNum()
{
	_gm->UpgradeShotNum();
	//UITitleUpdateButtons();
}
//void USA_UI_Title::ClickedUpgradePenetrate()
//{
//	_gm->UpgradePenetrate();
//	UITitleUpdateButtons();
//}