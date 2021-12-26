// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SA_UI_Master.h"
#include "SA_UI_Title.generated.h"

class ASA_PC;
class USA_UI_Upgrade;
class UButton;

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_UI_Title : public USA_UI_Master
{
	GENERATED_BODY()

public:
	void UITitleInit(ASA_PC* pc);
private:
	UPROPERTY(Meta = (BindWidget))
		USA_UI_Upgrade* _ui_upgrade = nullptr;

	UPROPERTY(Meta = (BindWidget))
		UButton* _wave_start = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UButton* _show_ui_upgrade = nullptr;

	UPROPERTY()
		ASA_PC* _pc = nullptr;



public:
	void UITitleUpdatePlayerDMG(const int32 i_dmg_update);

	UFUNCTION(BlueprintCallable)
		void ClickedShowUIUpgrade();
};
