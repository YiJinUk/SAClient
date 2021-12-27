// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Title/SA_UI_Title.h"
#include "Logic/SA_PC.h"
#include "Logic/SA_GM.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

void USA_UI_Title::NativeConstruct()
{
	Super::NativeConstruct();
	_dmg_upgrade_btn->OnClicked.AddDynamic(this, &USA_UI_Title::ClickedUpgradeDMG);
	_as_upgrade_btn->OnClicked.AddDynamic(this, &USA_UI_Title::ClickedUpgradeAS);
	_shot_num_upgrade_btn->OnClicked.AddDynamic(this, &USA_UI_Title::ClickedUpgradeShotNum);
	_penetrate_upgrade_btn->OnClicked.AddDynamic(this, &USA_UI_Title::ClickedUpgradePenetrate);
}
void USA_UI_Title::UITitleInit(ASA_PC* pc)
{
	_pc = pc;
	_gm = GetWorld()->GetAuthGameMode<ASA_GM>();
}

void USA_UI_Title::UITitleUpdatePlayerDMG(const int32 i_dmg_update)
{
	_dmg_upgrade->SetText(FText::AsNumber(i_dmg_update));
}
void USA_UI_Title::UITitleUpdatePlayerAS(const int32 i_as_update)
{
	_as_upgrade->SetText(FText::AsNumber(i_as_update));
}
void USA_UI_Title::UITitleUpdatePlayerShotNum(const int8 i_shot_num_update)
{
	_shot_num_upgrade->SetText(FText::AsNumber(i_shot_num_update));
}
void USA_UI_Title::UITitleUpdatePlayerPenetrate(const int8 i_penetrate)
{
	_penetrate_upgrade->SetText(FText::AsNumber(i_penetrate));
}

void USA_UI_Title::ClickedUpgradeDMG()
{
	_gm->UpgradeDMG();
}
void USA_UI_Title::ClickedUpgradeAS()
{
	_gm->UpgradeAS();
}
void USA_UI_Title::ClickedUpgradeShotNum()
{
	_gm->UpgradeShotNum();
}
void USA_UI_Title::ClickedUpgradePenetrate()
{
	_gm->UpgradePenetrate();
}