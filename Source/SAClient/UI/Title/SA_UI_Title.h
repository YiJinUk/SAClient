// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SA_UI_Master.h"
#include "SA_UI_Title.generated.h"

class ASA_PC;
class ASA_GM;
class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_UI_Title : public USA_UI_Master
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
public:
	void UITitleInit(ASA_PC* pc);
private:
	UPROPERTY(Meta = (BindWidget))
		UButton* _wave_start = nullptr;

	UPROPERTY(Meta = (BindWidget))
		UButton* _dmg_upgrade_btn = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _dmg_upgrade = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UButton* _as_upgrade_btn = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _as_upgrade = nullptr;

	UPROPERTY()
		ASA_PC* _pc = nullptr;
	UPROPERTY()
		ASA_GM* _gm = nullptr;
public:
	void UITitleUpdatePlayerDMG(const int32 i_dmg_update);
	void UITitleUpdatePlayerAS(const int32 i_as_update);

	UFUNCTION()
		void ClickedUpgradeDMG();
	UFUNCTION()
		void ClickedUpgradeAS();
};
