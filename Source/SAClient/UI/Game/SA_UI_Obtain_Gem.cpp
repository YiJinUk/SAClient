// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/SA_UI_Obtain_Gem.h"
#include "Logic/SA_PC.h"

#include "Components/TextBlock.h"

void USA_UI_Obtain_Gem::NativeConstruct()
{
	Super::NativeConstruct();

	_pc = Cast<ASA_PC>(GetOwningPlayer());
}

void USA_UI_Obtain_Gem::TimerPoolInWidget()
{
	_pc->PoolInUIObtainGem(this);
	RemoveFromViewport();
}

void USA_UI_Obtain_Gem::PlayAnim(const int32 i_obtain_gem)
{
	_gem->SetText(FText::AsNumber(i_obtain_gem));
	PlayAnimation(_obtain);

	GetWorld()->GetTimerManager().SetTimer(_timer_TimerPoolInWidget, this, &USA_UI_Obtain_Gem::TimerPoolInWidget, 2.f, false);
}