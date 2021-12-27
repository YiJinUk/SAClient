// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/SA_UI_WaveClear.h"
#include "Logic/SA_PC.h"

#include "Components/Button.h"

void USA_UI_WaveClear::NativeConstruct()
{
	Super::NativeConstruct();
	_pc = Cast<ASA_PC>(GetOwningPlayer());
	_next_wave->OnClicked.AddDynamic(this, &USA_UI_WaveClear::ClickedNextWave);
}

void USA_UI_WaveClear::ClickedNextWave()
{
	_pc->PCReturnTitle();
}