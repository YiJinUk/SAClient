// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SA_UI_Option.h"
#include "Logic/SA_GM.h"
#include "Logic/SA_PC.h"

#include "Components/Button.h"
#include "Components/CheckBox.h"

void USA_UI_Option::NativeConstruct()
{
	Super::NativeConstruct();

	_pc = Cast<ASA_PC>(GetOwningPlayer());
	_sagm = GetWorld()->GetAuthGameMode<ASA_GM>();
	//_sfx_toggle->OnClicked.AddDynamic(this, &USA_UI_Option::ClickedSFXToggle);
	_sfx_toggle->OnCheckStateChanged.AddDynamic(this, &USA_UI_Option::ClickedSFXToggle);
	_background_btn->OnClicked.AddDynamic(this, &USA_UI_Option::ClickedBackGroundBTN);
}

void USA_UI_Option::UIOptionSetCheckBoxSFX(const bool b_is_checked)
{
	_sfx_toggle->SetIsChecked(b_is_checked);
}

void USA_UI_Option::ClickedBackGroundBTN()
{
	_pc->SetPause(false);
	SetVisibility(ESlateVisibility::Hidden);
}

void USA_UI_Option::ClickedSFXToggle(const bool b_is_checked)
{
	_sagm->SFXToggle();
}