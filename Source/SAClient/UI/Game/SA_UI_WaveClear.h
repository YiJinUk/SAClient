// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "UI/SA_UI_Master.h"
#include "SA_UI_WaveClear.generated.h"

class ASA_PC;
class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_UI_WaveClear : public USA_UI_Master
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
private:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _obtain_gold = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _obtain_gem = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _kill_enemies = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _score = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UButton* _next_wave = nullptr;

	UPROPERTY(Meta = (BindWidgetAnim), Transient, Meta = (AllowPrivateAccess = true))
		UWidgetAnimation* _wave_clear = nullptr;

	UPROPERTY()
		ASA_PC* _pc = nullptr;

public:
	void UIWaveClearUpdate(const FInfoWaveClear& s_info_wave_clear);
	UFUNCTION()
		void ClickedNextWave();

};
