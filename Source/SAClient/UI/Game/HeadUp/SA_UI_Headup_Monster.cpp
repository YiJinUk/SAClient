// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/HeadUp/SA_UI_Headup_Monster.h"

#include "Components/TextBlock.h"

void USA_UI_Headup_Monster::UIInit(const int32 i_hp)
{
	_hp->SetText(FText::AsNumber(i_hp));
}