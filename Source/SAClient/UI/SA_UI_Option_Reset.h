// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SA_UI_Master.h"
#include "SA_UI_Option_Reset.generated.h"

class ASA_GM;
class UButton;

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_UI_Option_Reset : public USA_UI_Master
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
private:
	UPROPERTY(Meta = (BindWidget))
		UButton* _yes = nullptr;
	UPROPERTY()
		ASA_GM* _sagm = nullptr;
private:
	UFUNCTION()
		void ClickedResetYes();
};
