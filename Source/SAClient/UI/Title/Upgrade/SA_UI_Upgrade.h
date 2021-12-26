// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SA_UI_Master.h"
#include "SA_UI_Upgrade.generated.h"

class ASA_PC;
class ASA_GM;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_UI_Upgrade : public USA_UI_Master
{
	GENERATED_BODY()
	
public:
	void UIUpgradeInit(ASA_PC* pc);
private:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _dmg_upgrade = nullptr;
	UPROPERTY()
		ASA_PC* _pc = nullptr;
	UPROPERTY()
		ASA_GM* _gm = nullptr;


public:
	void UIUpgradeUpdatePlayerDMG(const int32 i_dmg_update);

	UFUNCTION(BlueprintCallable)
		void ClickedUpgradeDMG();
};
