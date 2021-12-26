// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SA_UI_Master.h"
#include "SA_UI_Headup_Monster.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_UI_Headup_Monster : public USA_UI_Master
{
	GENERATED_BODY()
	
public:
	void UIInit(const int32 i_hp);

private:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _hp = nullptr;
};
