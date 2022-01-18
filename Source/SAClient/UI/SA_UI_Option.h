// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SA_UI_Master.h"
#include "SA_UI_Option.generated.h"

class ASA_GM;
class ASA_PC;
class USA_UI_Option_Reset;
class UButton;
class UCheckBox;

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_UI_Option : public USA_UI_Master
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
private:
	UPROPERTY(Meta = (BindWidget))
		UButton* _background_btn = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UCheckBox* _sfx_toggle = nullptr;

	UPROPERTY(Meta = (BindWidget))
		UButton* _language_en_active = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UButton* _language_en_deactive = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UButton* _language_ko_active = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UButton* _language_ko_deactive = nullptr;

	UPROPERTY(Meta = (BindWidget))
		USA_UI_Option_Reset* _option_reset = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UButton* _reset = nullptr;

	UPROPERTY()
		ASA_GM* _sagm = nullptr;
	UPROPERTY()
		ASA_PC* _pc = nullptr;

public:
	void UIOptionSetCheckBoxSFX(const bool b_is_checked);
	void UIOptionSetLanguageBtn(const bool b_is_ko);
private:
	UFUNCTION()
		void ClickedBackGroundBTN();
	UFUNCTION()
		void ClickedSFXToggle(const bool b_is_checked);

	UFUNCTION()
		void ClickedLanguage_En();
	UFUNCTION()
		void ClickedLanguage_Ko();

	UFUNCTION()
		void ClickedReset();
};
