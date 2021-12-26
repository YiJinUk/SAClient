// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/SA_UI_GameOver.h"
#include "Logic/SA_PC.h"

void USA_UI_GameOver::UIGameOverInit(ASA_PC* pc)
{
	_pc = pc;
}

void USA_UI_GameOver::ClickedReturnTitle()
{
	_pc->PCReturnTitle();
	SetVisibility(ESlateVisibility::Hidden);
}