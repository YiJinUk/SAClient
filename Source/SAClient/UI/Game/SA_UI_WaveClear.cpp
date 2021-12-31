// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/SA_UI_WaveClear.h"
#include "Logic/SA_PC.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void USA_UI_WaveClear::NativeConstruct()
{
	Super::NativeConstruct();
	_pc = Cast<ASA_PC>(GetOwningPlayer());
	_next_wave->OnClicked.AddDynamic(this, &USA_UI_WaveClear::ClickedNextWave);
}

void USA_UI_WaveClear::UIWaveClearUpdate(const FInfoWaveClear& s_info_wave_clear)
{
	_obtain_gold->SetText(FText::AsNumber(s_info_wave_clear.obtain_gold));
	_obtain_gem->SetText(FText::AsNumber(s_info_wave_clear.obtain_gem));
	_kill_enemies->SetText(FText::AsNumber(s_info_wave_clear.kill_enemies));
	_score->SetText(FText::AsNumber(s_info_wave_clear.score));

	PlayAnimation(_wave_clear);
}

void USA_UI_WaveClear::ClickedNextWave()
{
	_pc->PCReturnTitle();
}