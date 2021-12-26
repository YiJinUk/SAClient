// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "GameFramework/PlayerController.h"
#include "SA_PC.generated.h"

class ASA_GM;
class USA_UI_Main;

/**
 * 
 */
UCLASS()
class SACLIENT_API ASA_PC : public APlayerController
{
	GENERATED_BODY()
	
protected:
	ASA_PC();

#pragma region Init
public:
	void PCInit(ASA_GM* sagm, FInfoPlayer& s_info_player);
protected:
	UFUNCTION(BlueprintImplementableEvent)
		void PCBPInit();
	UFUNCTION(BlueprintImplementableEvent)
		USA_UI_Main* PCCreateWidgetMain();
private:
	UPROPERTY()
		ASA_GM* _sagm = nullptr;
#pragma endregion

#pragma region Wave
public:
	void PCWaveStart();
	void PCWaveGameOver();
#pragma endregion

#pragma region Input
protected:
	virtual void SetupInputComponent() override;
private:
	void TapPressed();
private:
	UPROPERTY()
		FHitResult _tap_hit = FHitResult();
#pragma endregion

#pragma region UI
public:
	//매 프레임이 종료될 때 마다 호출합니다. 변경된 정보만 업데이트 합니다
	void PCUIUpdateCheck();

	void PCReturnTitle();
private:
	UPROPERTY()
		USA_UI_Main* _ui_main = nullptr;
	UPROPERTY()
		FInfoPlayer _ui_info_player;
#pragma endregion	
};
