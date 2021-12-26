// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/SA_GI.h"

USA_GI::USA_GI()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MONSTER(TEXT("/Game/SAContent/ReadOnly/Data/SADT_Monster.SADT_Monster"));
	if (DT_MONSTER.Succeeded())
		_dt_monster = DT_MONSTER.Object;
	
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_GAME(TEXT("/Game/SAContent/ReadOnly/Data/SADT_Game.SADT_Game"));
	if (DT_GAME.Succeeded())
		_dt_game = DT_GAME.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PROJECTILE(TEXT("/Game/SAContent/ReadOnly/Data/SADT_Projectile.SADT_Projectile"));
	if (DT_PROJECTILE.Succeeded())
		_dt_projectile = DT_PROJECTILE.Object;
}

void USA_GI::GIInit()
{
	_data_game = _dt_game->FindRow<FDataGame>("GAME00001", "0");
}

FDataMonster* USA_GI::FindDataMonsterByCode(const FString& str_code_monster)
{
	if (!_dt_monster) return nullptr;
	return _dt_monster->FindRow<FDataMonster>(*str_code_monster, "0");
}
FDataProjectile* USA_GI::FindDataPROJByCode(const FString& str_code_proj)
{
	if (!_dt_projectile) return nullptr;
	return _dt_projectile->FindRow<FDataProjectile>(*str_code_proj, "0");
}

FDataGame* USA_GI::GetDataGame() { return _data_game; }