// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SA_UI_Option_Reset.h"
#include "Logic/SA_GM.h"

#include "Components/Button.h"

void USA_UI_Option_Reset::NativeConstruct()
{
	Super::NativeConstruct();

	_sagm = GetWorld()->GetAuthGameMode<ASA_GM>();

	_yes->OnClicked.AddDynamic(this, &USA_UI_Option_Reset::ClickedResetYes);
}

void USA_UI_Option_Reset::ClickedResetYes()
{
	SetVisibility(ESlateVisibility::Hidden);
	_sagm->DebugInitPlayer();
}