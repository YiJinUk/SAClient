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
	_language_en_deactive->OnClicked.AddDynamic(this, &USA_UI_Option::ClickedLanguage_En);
	_language_ko_deactive->OnClicked.AddDynamic(this, &USA_UI_Option::ClickedLanguage_Ko);

	_language_en_active->SetVisibility(ESlateVisibility::Hidden);
	_language_en_deactive->SetVisibility(ESlateVisibility::Hidden);
	_language_ko_active->SetVisibility(ESlateVisibility::Hidden);
	_language_ko_deactive->SetVisibility(ESlateVisibility::Hidden);
}

void USA_UI_Option::UIOptionSetCheckBoxSFX(const bool b_is_checked)
{
	_sfx_toggle->SetIsChecked(b_is_checked);
}
void USA_UI_Option::UIOptionSetLanguageBtn(const bool b_is_ko)
{
	if (b_is_ko)
	{
		_language_ko_active->SetVisibility(ESlateVisibility::Visible);
		_language_ko_deactive->SetVisibility(ESlateVisibility::Hidden);

		_language_en_active->SetVisibility(ESlateVisibility::Hidden);
		_language_en_deactive->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		_language_ko_active->SetVisibility(ESlateVisibility::Hidden);
		_language_ko_deactive->SetVisibility(ESlateVisibility::Visible);

		_language_en_active->SetVisibility(ESlateVisibility::Visible);
		_language_en_deactive->SetVisibility(ESlateVisibility::Hidden);
	}
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

void USA_UI_Option::ClickedLanguage_En()
{
	_sagm->SetLanguage("en");
}
void USA_UI_Option::ClickedLanguage_Ko()
{
	_sagm->SetLanguage("ko_kr");
}