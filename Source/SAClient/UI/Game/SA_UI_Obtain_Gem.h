// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SA_UI_Master.h"
#include "SA_UI_Obtain_Gem.generated.h"

class ASA_PC;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_UI_Obtain_Gem : public USA_UI_Master
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
private:
	void TimerPoolInWidget();
private:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _gem = nullptr;

	UPROPERTY(Meta = (BindWidgetAnim), Transient, Meta = (AllowPrivateAccess = true))
		UWidgetAnimation* _obtain = nullptr;

	UPROPERTY()
		ASA_PC* _pc = nullptr;

	UPROPERTY()
		FTimerHandle _timer_TimerPoolInWidget;

public:
	void PlayAnim(const int32 i_obtain_gem);
};
