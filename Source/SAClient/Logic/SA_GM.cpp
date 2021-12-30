// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/SA_GM.h"
#include "SA_FunctionLibrary.h"
#include "SA_GI.h"
#include "SA_PC.h"
#include "Manager/SA_Manager_Pool.h"
#include "Manager/SA_Manager_Battle.h"
#include "Manager/SA_Manager_SFX.h"
#include "Manager/SA_Manager_SaveLoad.h"
#include "Actor/Unit/Player/SA_Player.h"
#include "Actor/Unit/Monster/SA_Monster.h"
#include "Actor/Object/SA_SpawnPoint.h"
#include "Actor/Object/Projectile/SA_Projectile.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "DrawDebugHelpers.h"

void ASA_GM::DebugWaveStart()
{
	WaveStart();
}

ASA_GM::ASA_GM()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASA_GM::PostLogin(APlayerController* NewPlayer)
{
	/*앱을 최초로 실행시켰습니다 초기화를 진행합니다*/
	_pc = Cast<ASA_PC>(NewPlayer);

	GMInit();
}

void ASA_GM::GMInit()
{
	UWorld* wld = GetWorld();
	_sagi = wld->GetGameInstance<USA_GI>();
	if (!_sagi) //Err
	{
		//게임인스턴스를 불러올 수 없습니다
	}

	/*게임인스턴스 초기화*/
	_sagi->GIInit();

	/*자주 사용하는 게임데이터를 캐싱합니다*/
	_data_game_cache = _sagi->GetDataGame();

	/*맵에 생성된 플레이어를 가져옵니다*/
	TArray<AActor*> arr_found_actor;
	UGameplayStatics::GetAllActorsOfClass(wld, ASA_Player::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1)
	{
		_player_chr = Cast<ASA_Player>(arr_found_actor[0]);
		if (!_player_chr) // Err
		{
			//플레이어 캐릭터를 찾을 수 없습니다
		}
		_player_loc = _player_chr->GetActorLocation();
	}

	/*맵에 생성된 몬스터 스폰포인트를 가져옵니다*/
	UGameplayStatics::GetAllActorsOfClass(wld, ASA_SpawnPoint::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1)
	{
		ASA_SpawnPoint* spawn_point = nullptr;
		for (AActor* actor_found : arr_found_actor)
		{
			spawn_point = Cast<ASA_SpawnPoint>(actor_found);
			if (spawn_point)
			{
				spawn_point->SpawnPointInit(_player_loc);
				_mob_spawn_points.Emplace(spawn_point);
			}
		}
	}

	/*매니저를 생성합니다*/
	//생성 객체 만들기
	FActorSpawnParameters s_param;
	s_param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	_manager_pool = wld->SpawnActor<ASA_Manager_Pool>(s_param); // 풀링 매니저
	_manager_battle = wld->SpawnActor<ASA_Manager_Battle>(s_param); // 전투 매니저
	_manager_sfx = wld->SpawnActor<ASA_Manager_SFX>(s_param); // 사운드 매니저
	_manager_saveload = wld->SpawnActor<ASA_Manager_SaveLoad>(s_param); // 세이브로드 매니저
	

	/*버그방지를 위해 모든 매니저를 생성하고 한번에 초기화합니다*/
	_manager_pool->PoolInit(_sagi);
	_manager_battle->BattleInit(this);
	_manager_sfx->SFXInit(_sagi);

	/*발사체 정보를 초기화합니다*/
	_proj_loc_start_3d = FVector(_player_loc.X, _player_loc.Y, _data_game_cache->GetPROJZFixed());
	_proj_loc_start_2d = FVector2D(_player_loc.X, _player_loc.Y);
	_proj_velocity = FVector2D(1.f, 0.f);

	/*배경음악 재생*/
	_manager_sfx->SFXStart(ESFXType::BACKGROUND);

	/*플레이어의 세이브데이터를 불러옵니다*/
	GameLoad();
	//_info_player.SetGold(10);
	//_info_player.SetDMG(1);
	//_info_player.SetAS(60);
	//_info_player.SetShotNumber(1);
	//_info_player.SetPenetrate(1);

	/*플레이어를 초기화합니다*/
	_pc->PCInit(this, _info_player_chr);

	/*로드한 정보를 통해 사운드를 초기화합니다*/
	_info_option.is_sfx_on = !_info_option.is_sfx_on;
	SFXToggle();

	ReturnTitle();
}

void ASA_GM::InitInfoPlayerChr()
{
	/*플레이어정보 초기화*/
	_info_player_chr.hp = _data_game_cache->GetPlayetHP();
	_info_player_chr.dmg = _info_player.GetDMG();
	_info_player_chr.as = _info_player.GetAS();

	_info_player_chr.as_wait = 0;
}

void ASA_GM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (_wave_status == EWaveStatus::PLAY)
	{
		++_tick;

		/*몬스터를 생성합니다*/
		TickSpawnMonster();

		/*발사체 발사 검사*/
		TickCheckShootPROJ();

		/*몬스터 이동 및 도착*/
		TickMoveMonster(DeltaTime);

		/*발사체 이동 및 공격*/
		TickMovePROJ(DeltaTime);

		/*트레저체스트를 생성하는지*/
		TickCheckSpawnTreasuerChest();


		/*UI Update*/
		_pc->PCUIUpdateCheck();

		TickCheckWaveEnd();
	}
}

void ASA_GM::TickSpawnMonster()
{
	if (_tick % _data_wave_current.GetSpawnTickInterval() == 0)
	{
		const int16 i_max_spawn_on_1_tick = _data_wave_current.GetMaxSpawnOn1Tick();
		TArray<FDataWaveMonster>& arr_data_spawn_monster = _data_wave_current.GetSpawnMonsters();
		ASA_SpawnPoint* spawn_point_rnd = nullptr;
		ASA_Monster* spawn_monster = nullptr;
		for (int16 i = 0; i < i_max_spawn_on_1_tick; ++i)
		{
			for (FDataWaveMonster& s_data_spawn_monster : arr_data_spawn_monster)
			{
				if (s_data_spawn_monster.GetSpawnCount() <= 0) continue;

				/*생성 성공*/
				s_data_spawn_monster.SubSpawnCount();
				spawn_point_rnd = GetRandomSpawnPoint();
				spawn_monster = _manager_pool->PoolGetMonsterByCode(s_data_spawn_monster.GetCodeMonster());
				spawn_monster->MOBInit(GetNewId(), s_data_spawn_monster.GetMonsterHP(), spawn_point_rnd);
				_spawn_monsters.Add(spawn_monster);
				++_count_spawn_monster_current;
				break;
			}
		}
	}
}

void ASA_GM::TickCheckShootPROJ()
{
	++_info_player_chr.as_wait;
	if (_info_player_chr.as_wait >= _info_player_chr.GetASTotal())
	{
		/*발사*/
		_info_player_chr.as_wait = 0;
		ShootPROJ();
	}
}

void ASA_GM::TickMoveMonster(const float f_delta_time)
{
	ASA_Monster* spawn_monster = nullptr;
	for (int32 i = _spawn_monsters.Num() - 1; i >= 0; --i)
	{
		spawn_monster = _spawn_monsters[i];

		/*Move*/
		spawn_monster->MOBMove(f_delta_time);

		/*Check Arrive*/
		if (USA_FunctionLibrary::GetDistanceByV3(spawn_monster->GetActorLocation(), _player_loc) <= _data_game_cache->GetDestRadius())
		{
			//Arrive!
			if (spawn_monster->GetInfoMonster().is_treasure_chest)
			{
				_is_death_treasure_chest = true;
			}
			else
			{
				--_info_player_chr.hp;
			}
			
			_manager_pool->PoolInMonster(spawn_monster);
			_spawn_monsters.RemoveAt(i);
		}
	}
}

void ASA_GM::TickMovePROJ(const float f_delta_time)
{
	ASA_Projectile* spawn_proj = nullptr;
	ASA_Monster* spawn_monster = nullptr;
	for (int32 i = _spawn_projs.Num() - 1; i >= 0; --i)
	{
		spawn_proj = _spawn_projs[i];

		/*Debug*/
		DrawDebugCircle(GetWorld(), spawn_proj->GetActorLocation(), _data_game_cache->GetPROJRange(), 30, FColor::Red, false, -1.f, 0, 0.f, FVector(1.f, 0.f, 0.f), FVector(0.f, 1.f, 0.f));

		/*Move*/
		spawn_proj->PROJMove(f_delta_time, _data_game_cache->GetPROJSpeed());

		/*Max_Distance*/
		if (USA_FunctionLibrary::GetDistanceByV3(spawn_proj->GetActorLocation(), _player_loc) >= 2500.f)
		{
			_manager_pool->PoolInPROJ(spawn_proj);
			_spawn_projs.RemoveAt(i);
			break;
		}

		/*Find Target*/
		for (int32 j = _spawn_monsters.Num() - 1; j >= 0; --j)
		{
			spawn_monster = _spawn_monsters[j];

			if (USA_FunctionLibrary::GetDistanceByV2(spawn_proj->GetActorLocation2D(), spawn_monster->GetActorLocation2D()) <= _data_game_cache->GetPROJRange())
			{
				//Arrive!
				_manager_sfx->SFXStart(ESFXType::PROJ_HIT);
				/*이미 공격한 몬스터인지 확인합니다*/
				if (spawn_proj->PROJIsAttackedMonsterByMOBId(spawn_monster->GetInfoMonster().id)) continue;

				/*공격시도후 몬스터가 죽었다면 몬스터를 풀링합니다*/
				if (_manager_battle->BattleCalcStart(spawn_proj, spawn_monster, _info_player_chr.GetDMGTotal()))
				{
					if (spawn_monster->GetInfoMonster().is_treasure_chest)
					{
						_is_death_treasure_chest = true;
					}
					else
					{
						SpawnMonsterClone(spawn_monster);
					}

					_manager_pool->PoolInMonster(spawn_monster);
					_spawn_monsters.RemoveAt(j);
				}

				/*발사체가 풀에 들어가야하는지 검증합니다*/
				if (spawn_proj->PROJIsDoPoolIn(_info_player.GetPenetrate()))
				{
					_manager_pool->PoolInPROJ(spawn_proj);
					_spawn_projs.RemoveAt(i);
					break;
				}
			}
		}
	}
}

void ASA_GM::TickCheckSpawnTreasuerChest()
{
	if (_is_death_treasure_chest) return;

	if (_tick % 60 == 0)
	{
		if (_count_spawn_monster_max <= _count_spawn_monster_current && _spawn_monsters.Num() <= 0)
		{
			/*Spawn TreasureChest*/
			int32 i_hp_treasure_chest = 0;
			for (const FDataWaveMonster& s_data_wave_monster : _data_wave_current.GetSpawnMonsters())
			{
				//s_data_wave.
				i_hp_treasure_chest += _sagi->GetMonsterHPByEnum(s_data_wave_monster.GetMonsterHP());
			}
			ASA_Monster* spawn_treasure_chest = _manager_pool->PoolGetMonsterByCode("MOB00010");
			spawn_treasure_chest->MOBInitTreasureChest(GetNewId(), i_hp_treasure_chest, _data_game_cache->GetTreasureChestSpawnLoc());
			_spawn_monsters.Add(spawn_treasure_chest);
		}
	}
}

void ASA_GM::TickCheckWaveEnd()
{
	/*플레이어의 체력이 0이하로 떨어지면 게임이 종료됩니다*/
	if (_info_player_chr.hp <= 0)
	{
		WaveGameOver();
	}
	else
	{
		if (_tick % 30 == 0)
		{
			if (_is_death_treasure_chest)
			{
				WaveClear();
			}
		}
	}
}

void ASA_GM::ReturnTitle()
{
	PoolInAllSpawnedMonsters();
	PoolInAllSpawnedPROJs();

	InitInfoPlayerChr();

	SetWaveStatus(EWaveStatus::TITLE);
}

void ASA_GM::WaveStart()
{
	_tick = 0;
	_count_spawn_monster_current = 0;
	_count_spawn_monster_max = 0;
	_is_death_treasure_chest = false;

	/*해당 웨이브에서 생성되는 몬스터정보를 가져옵니다*/
	FDataWave* s_data_wave = _sagi->FindDataWaveByWaveRound(_wave_round_current);
	if(s_data_wave)
		_data_wave_current = *s_data_wave;
	else
	{
		//Err 시작할 웨이브데이터가 없습니다. 1웨이브로 돌아갑니다
		_wave_round_current = 1;
		s_data_wave = _sagi->FindDataWaveByWaveRound(_wave_round_current);
		if (s_data_wave)
			_data_wave_current = *s_data_wave;
	}
	if (s_data_wave)
	{
		const TArray<FDataWaveMonster>& arr_data_spawn_monster = _data_wave_current.GetSpawnMonsters();
		for (const FDataWaveMonster& s_data_spawn_monster : arr_data_spawn_monster)
		{
			_count_spawn_monster_max += s_data_spawn_monster.GetSpawnCount();
		}
	}

	//세이브
	GameSave();

	InitInfoPlayerChr();

	_pc->PCWaveStart();

	SetWaveStatus(EWaveStatus::PLAY);
}

void ASA_GM::WaveClear()
{
	SetWaveStatus(EWaveStatus::CLEAR);
	++_wave_round_current;
	_pc->PCWaveClear(_wave_round_current);

	//세이브
	GameSave();
}

void ASA_GM::WaveGameOver()
{
	GameSave();

	/*게임오버*/
	SetWaveStatus(EWaveStatus::GAMEOVER);

	_pc->PCWaveGameOver();
}

void ASA_GM::ShootPROJ()
{	
	for (int32 i = 0; i < _info_player.GetShotNumber(); ++i)
	{
		ASA_Projectile* spawn_proj = _manager_pool->PoolGetPROJByCode("PROJ00001");
		spawn_proj->PROJInit(GetNewId(), _proj_loc_start_3d + _data_game_cache->GetPROJShopLoc()[i], _proj_velocity, 0.f);
		_spawn_projs.Add(spawn_proj);
	}

	_manager_sfx->SFXStart(ESFXType::PROJ_SHOT);
}

void ASA_GM::ChangePROJVelocity(const FVector& v_dest)
{
	_proj_velocity = USA_FunctionLibrary::GetVelocityByV2(_proj_loc_start_2d, FVector2D(v_dest.X, v_dest.Y));
}

void ASA_GM::SpawnMonsterClone(ASA_Monster* monster_origin)
{
	const EMonsterHP e_monster_hp_origin = monster_origin->GetDownMonsterHP();
	if (e_monster_hp_origin == EMonsterHP::HP_NO) return;

	const FVector& v_loc_spawn_origin = monster_origin->GetActorLocation();
	FVector v_loc_spawn_new = FVector(v_loc_spawn_origin.X, v_loc_spawn_origin.Y + _data_game_cache->GetMonsterCloneLocY(), 0.f);
	
	for (int32 i = 0; i < 2; ++i)
	{
		ASA_Monster* spawn_monster_new = _manager_pool->PoolGetMonsterByCode(monster_origin->GetInfoMonster().code);
		if (i == 1)
			v_loc_spawn_new.Y = -v_loc_spawn_new.Y;
		spawn_monster_new->MOBInitClone(GetNewId(), monster_origin->GetDownMonsterHP(), v_loc_spawn_new, USA_FunctionLibrary::GetVelocityByV3(v_loc_spawn_new, _player_loc), FRotator(0.f, USA_FunctionLibrary::GetLookRotatorYawByV3(v_loc_spawn_new, _player_loc), 0.f));
		_spawn_monsters.Add(spawn_monster_new);
	}
}

void ASA_GM::PoolInAllSpawnedPROJs()
{
	ASA_Projectile* spawn_proj = nullptr;
	for (int32 i = _spawn_projs.Num() - 1; i >= 0; --i)
	{
		spawn_proj = _spawn_projs[i];
		_manager_pool->PoolInPROJ(spawn_proj);
	}
	_spawn_projs.Empty(100);
}

void ASA_GM::PoolInAllSpawnedMonsters()
{
	ASA_Monster* spawn_monster = nullptr;
	for (int32 i = _spawn_monsters.Num() - 1; i >= 0; --i)
	{
		spawn_monster = _spawn_monsters[i];
		_manager_pool->PoolInMonster(spawn_monster);
	}
	_spawn_monsters.Empty(100);
}

void ASA_GM::SFXToggle()
{
	_info_option.is_sfx_on = !_info_option.is_sfx_on;
	BPSFXToggle(_info_option.is_sfx_on);
	GameSaveOption();
}

void ASA_GM::UpgradeDMG()
{
	if (_info_player.GetGold() < 1)
	{
		return; // 소지금 부족
	}

	/*구매가능*/
	PlayerChangeStat(EPlayerStat::GOLD, 1, false);
	PlayerChangeStat(EPlayerStat::DMG, 1, true);
}
void ASA_GM::UpgradeAS()
{
	if (_info_player.GetGold() < 1)
	{
		return; // 소지금 부족
	}

	/*구매가능*/
	PlayerChangeStat(EPlayerStat::GOLD, 1, false);
	PlayerChangeStat(EPlayerStat::AS, 6, false);// 공속이 증가하기 위해 다음공격딜레이 시간을 줄여야 합니다
}
void ASA_GM::UpgradeShotNum()
{
	if (_info_player.GetGold() < 1)
	{
		return; // 소지금 부족
	}

	/*구매가능*/
	PlayerChangeStat(EPlayerStat::GOLD, 1, false);
	PlayerChangeStat(EPlayerStat::SHOT_NUMBER, 1, true);
}
void ASA_GM::UpgradePenetrate()
{
	if (_info_player.GetGold() < 1)
	{
		return; // 소지금 부족
	}

	/*구매가능*/
	PlayerChangeStat(EPlayerStat::GOLD, 1, false);
	PlayerChangeStat(EPlayerStat::PENETRATE, 1, true);
}

void ASA_GM::PlayerChangeStat(const EPlayerStat e_player_stat, const int32 i_value, const bool b_is_add)
{
	switch (e_player_stat)
	{
	case EPlayerStat::GOLD:
		if(b_is_add)
			_info_player.SetGold(_info_player.GetGold() + i_value);
		else
			_info_player.SetGold(_info_player.GetGold() - i_value);

		_pc->PCUIUpdatePlayerStat(e_player_stat, _info_player.GetGold());
		break;
	case EPlayerStat::DMG:
		if (b_is_add)
			_info_player.SetDMG(_info_player.GetDMG() + i_value);
		else
			_info_player.SetDMG(_info_player.GetDMG() - i_value);

		_pc->PCUIUpdatePlayerStat(e_player_stat, _info_player.GetDMG());
		break;
	case EPlayerStat::AS:
		if (b_is_add)
			_info_player.SetAS(_info_player.GetAS() + i_value);
		else
			_info_player.SetAS(_info_player.GetAS() - i_value);

		_pc->PCUIUpdatePlayerStat(e_player_stat, _info_player.GetAS());
		break;
	case EPlayerStat::SHOT_NUMBER:
		if (b_is_add)
			_info_player.SetShotNumber(_info_player.GetShotNumber() + i_value);
		else
			_info_player.SetShotNumber(_info_player.GetShotNumber() - i_value);

		_pc->PCUIUpdatePlayerStat(e_player_stat, _info_player.GetShotNumber());
		break;
	case EPlayerStat::PENETRATE:
		if (b_is_add)
			_info_player.SetPenetrate(_info_player.GetPenetrate() + i_value);
		else
			_info_player.SetPenetrate(_info_player.GetPenetrate() - i_value);

		_pc->PCUIUpdatePlayerStat(e_player_stat, _info_player.GetPenetrate());
		break;
	default:
		break;
	}
}

void ASA_GM::GameSave()
{
	_manager_saveload->SaveStart(_info_player, _wave_round_current);
}
void ASA_GM::GameSaveOption()
{
	_manager_saveload->SaveOptionStart(_info_option);
}
void ASA_GM::GameLoad()
{
	_manager_saveload->ReadStart(_info_player, _wave_round_current, _info_option);
}

const int64 ASA_GM::GetNewId() { return ++_id_master; }
ASA_SpawnPoint* ASA_GM::GetRandomSpawnPoint() { return _mob_spawn_points[UKismetMathLibrary::RandomInteger(_mob_spawn_points.Num())]; }
const FInfoPlayerCharacter& ASA_GM::GetInfoPlayerChr() const { return _info_player_chr; }
const FInfoPlayer& ASA_GM::GetInfoPlayer() const { return _info_player; }
void ASA_GM::SetWaveStatus(const EWaveStatus e_wave_status) { _wave_status = e_wave_status; }
const int32 ASA_GM::GetWaveRoundCurrent() const { return _wave_round_current; }
