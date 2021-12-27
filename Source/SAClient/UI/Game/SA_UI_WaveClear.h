// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SA_UI_Master.h"
#include "SA_UI_WaveClear.generated.h"

class ASA_PC;
class UButton;

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
		UButton* _next_wave = nullptr;
	UPROPERTY()
		ASA_PC* _pc = nullptr;

public:
	UFUNCTION()
		void ClickedNextWave();

};
