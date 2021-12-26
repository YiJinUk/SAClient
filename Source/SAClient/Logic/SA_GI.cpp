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

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_WAVES(TEXT("/Game/SAContent/ReadOnly/Data/SADT_Waves.SADT_Waves"));
	if (DT_WAVES.Succeeded())
		_dt_waves = DT_WAVES.Object;
}

void USA_GI::GIInit()
{
	_data_game = _dt_game->FindRow<FDataGame>("GAME00001", "0");
	_data_waves = _dt_waves->FindRow<FDataWaves>("WAVES00001", "0");
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
FDataWave* USA_GI::FindDataWaveByWaveRound(const int32 i_wave_round)
{
	if (i_wave_round > _data_waves->GetWaves().Num()) return nullptr;
	return &_data_waves->GetWaves()[i_wave_round - 1];

	return nullptr;
}

FDataGame* USA_GI::GetDataGame() { return _data_game; }