// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Title/SA_UI_Title.h"
#include "Logic/SA_PC.h"
#include "Upgrade/SA_UI_Upgrade.h"

void USA_UI_Title::UITitleInit(ASA_PC* pc)
{
	_pc = pc;
	_ui_upgrade->UIUpgradeInit(pc);
}

void USA_UI_Title::ClickedShowUIUpgrade()
{
	_ui_upgrade->SetVisibility(ESlateVisibility::Visible);
}

void USA_UI_Title::UITitleUpdatePlayerDMG(const int32 i_dmg_update)
{
	_ui_upgrade->UIUpgradeUpdatePlayerDMG(i_dmg_update);
}