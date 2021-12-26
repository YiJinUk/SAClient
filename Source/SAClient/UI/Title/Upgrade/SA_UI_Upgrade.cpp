// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Title/Upgrade/SA_UI_Upgrade.h"
#include "Logic/SA_PC.h"
#include "Logic/SA_GM.h"

#include "Components/TextBlock.h"

void USA_UI_Upgrade::UIUpgradeInit(ASA_PC* pc)
{
	_pc = pc;
	_gm = GetWorld()->GetAuthGameMode<ASA_GM>();
}

void USA_UI_Upgrade::UIUpgradeUpdatePlayerDMG(const int32 i_dmg_update)
{
	_dmg_upgrade->SetText(FText::AsNumber(i_dmg_update));
}

void USA_UI_Upgrade::ClickedUpgradeDMG()
{
	_gm->UpgradeDMG();
}