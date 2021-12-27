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

}
void USA_UI_Title::UITitleInit(ASA_PC* pc)
{
	_pc = pc;
	_gm = GetWorld()->GetAuthGameMode<ASA_GM>();

	//_dmg_upgrade_btn->OnClicked.AddDynamic(this, &USA_UI_Title::ClickedUpgradeDMG);
	//_as_upgrade_btn->OnClicked.AddDynamic(this, &USA_UI_Title::ClickedUpgradeAS);
}

void USA_UI_Title::UITitleUpdatePlayerDMG(const int32 i_dmg_update)
{
	_dmg_upgrade->SetText(FText::AsNumber(i_dmg_update));
}
void USA_UI_Title::UITitleUpdatePlayerAS(const int32 i_as_update)
{
	_as_upgrade->SetText(FText::AsNumber(i_as_update));
}

void USA_UI_Title::ClickedUpgradeDMG()
{
	_gm->UpgradeDMG();
}
void USA_UI_Title::ClickedUpgradeAS()
{
	_gm->UpgradeAS();
}