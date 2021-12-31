// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SA_UI_Master.h"
#include "SA_UI_GameOver.generated.h"

class ASA_PC;

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_UI_GameOver : public USA_UI_Master
{
	GENERATED_BODY()

public:
	void UIGameOverInit(ASA_PC* pc);
private:
	UPROPERTY(Meta = (BindWidgetAnim), Transient, Meta = (AllowPrivateAccess = true))
		UWidgetAnimation* _game_over = nullptr;

	UPROPERTY()
		ASA_PC* _pc = nullptr;
public:
	void UIGameOverUpdate();
	UFUNCTION(BlueprintCallable)
		void ClickedReturnTitle();
};
