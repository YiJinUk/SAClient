// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "UI/SA_UI_Master.h"
#include "SA_UI_Game.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_UI_Game : public USA_UI_Master
{
	GENERATED_BODY()

public:
	void UIPlayerUpdateCheck(const FInfoPlayer& s_info_player_new, const FInfoPlayer& s_info_player_old);
	
private:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _hp = nullptr;

public:
	FORCEINLINE void SetHP(const int32 i_hp);
};
