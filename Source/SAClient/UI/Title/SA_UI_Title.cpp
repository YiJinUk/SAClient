// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Title/SA_UI_Title.h"
#include "Logic/SA_PC.h"
#include "Upgrade/SA_UI_Upgrade.h"

void USA_UI_Title::UITitleInit(ASA_PC* pc)
{
	_pc = pc;
}

void USA_UI_Title::ClickedShowUIUpgrade()
{
	_ui_upgrade->SetVisibility(ESlateVisibility::Visible);
}