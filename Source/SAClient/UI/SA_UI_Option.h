// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SA_UI_Master.h"
#include "SA_UI_Option.generated.h"

class ASA_GM;
class ASA_PC;
class UButton;

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
		UButton* _sfx_toggle = nullptr;

	UPROPERTY()
		ASA_GM* _sagm = nullptr;
	UPROPERTY()
		ASA_PC* _pc = nullptr;

private:
	UFUNCTION()
		void ClickedBackGroundBTN();
	UFUNCTION()
		void ClickedSFXToggle();
};
