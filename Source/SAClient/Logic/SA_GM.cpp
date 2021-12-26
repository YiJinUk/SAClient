// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/SA_GM.h"
#include "SA_FunctionLibrary.h"
#include "SA_GI.h"
#include "SA_PC.h"
#include "Manager/SA_Manager_Pool.h"
#include "Manager/SA_Manager_Battle.h"
#include "Actor/Unit/Player/SA_Player.h"
#include "Actor/Unit/Monster/SA_Monster.h"
#include "Actor/Object/SA_SpawnPoint.h"
#include "Actor/Object/Projectile/SA_Projectile.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void ASA_GM::DebugWaveStart()
{
	WaveStart();
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

	/*버그방지를 위해 모든 매니저를 생성하고 한번에 초기화합니다*/
	_manager_pool->PoolInit(_sagi);

	/*발사체 정보를 초기화합니다*/
	_proj_loc_start_3d = FVector(_player_loc.X, _player_loc.Y, _data_game_cache->GetPROJZFixed());
	_proj_loc_start_2d = FVector2D(_player_loc.X, _player_loc.Y);
	_proj_velocity = FVector2D(1.f, 0.f);

	/*플레이어를 초기화합니다*/
	InitInfoPlayer();
	_pc->PCInit(this, _info_player);
}

void ASA_GM::InitInfoPlayer()
{
	/*플레이어정보 초기화*/
	_info_player.hp = _data_game_cache->GetPlayetHP();
	_info_player.dmg = 1;
	_info_player.as = 60;

	_info_player.as_wait = 0;
}

void ASA_GM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (_wave_status == EWaveStatus::PLAY)
	{
		++_tick;

		if (_tick % 60 == 0)
		{
			ASA_SpawnPoint* spawn_point_rnd = nullptr;
			ASA_Monster* spawn_monster = nullptr;
			for (int32 i = 0; i < 1; ++i)
			{
				spawn_point_rnd = GetRandomSpawnPoint();
				spawn_monster = _manager_pool->PoolGetMonsterByCode("MOB00001");
				spawn_monster->MOBInit(GetNewId(), spawn_point_rnd->GetPointSpawnLocation(), spawn_point_rnd->GetPointVelocity(), spawn_point_rnd->GetPointRotator());
				_spawn_monsters.Add(spawn_monster);
			}
		}

		/*발사체 발사 검사*/
		++_info_player.as_wait;
		if (_info_player.as_wait >= _info_player.GetASTotal())
		{
			/*발사*/
			_info_player.as_wait = 0;
			ShootPROJ();
		}


		ASA_Monster* spawn_monster = nullptr;
		for (int32 i = _spawn_monsters.Num() - 1; i >= 0; --i)
		{
			spawn_monster = _spawn_monsters[i];

			/*Move*/
			spawn_monster->MOBMove(DeltaTime);

			/*Check Arrive*/
			if (USA_FunctionLibrary::GetDistanceByV3(spawn_monster->GetActorLocation(), _player_loc) <= _data_game_cache->GetDestRadius())
			{
				//Arrive!
				_manager_pool->PoolInMonster(spawn_monster);
				--_info_player.hp;
				_spawn_monsters.RemoveAt(i);
			}
		}

		ASA_Projectile* spawn_proj = nullptr;
		for (int32 i = _spawn_projs.Num() - 1; i >= 0; --i)
		{
			spawn_proj = _spawn_projs[i];

			/*Move*/
			spawn_proj->PROJMove(DeltaTime, _data_game_cache->GetPROJSpeed());
		}

		if (_tick % 4 == 0)
		{
			for (int32 i = _spawn_projs.Num() - 1; i >= 0; --i)
			{
				spawn_proj = _spawn_projs[i];

				/*Find Target*/
				for (int32 j = _spawn_monsters.Num() - 1; j >= 0; --j)
				{
					spawn_monster = _spawn_monsters[j];

					if (USA_FunctionLibrary::GetDistanceByV2(spawn_proj->GetActorLocation2D(), spawn_monster->GetActorLocation2D()) <= _data_game_cache->GetPROJRange())
					{
						//Arrive!
						if (_manager_battle->BattleCalcStart(spawn_proj, spawn_monster, _info_player.GetDMGTotal()))
						{
							_manager_pool->PoolInMonster(spawn_monster);
							_spawn_monsters.RemoveAt(j);
						}

						_manager_pool->PoolInPROJ(spawn_proj);
						_spawn_projs.RemoveAt(i);
						break;
					}
				}
			}
		}

		/*UI Update*/
		_pc->PCUIUpdateCheck();

		WaveEndCheck();
	}
}

void ASA_GM::ReturnTitle()
{
	ASA_Monster* spawn_monster = nullptr;
	for (int32 i = _spawn_monsters.Num() - 1; i >= 0; --i)
	{
		spawn_monster = _spawn_monsters[i];
		_manager_pool->PoolInMonster(spawn_monster);
	}
	_spawn_monsters.Empty(100);

	InitInfoPlayer();

	SetWaveStatus(EWaveStatus::TITLE);
}

void ASA_GM::WaveStart()
{
	_tick = 0;

	_pc->PCWaveStart();

	SetWaveStatus(EWaveStatus::PLAY);
}

void ASA_GM::WaveEndCheck()
{
	/*플레이어의 체력이 0이하로 떨어지면 게임이 종료됩니다*/
	if (_info_player.hp <= 0)
	{
		/*게임오버*/
		SetWaveStatus(EWaveStatus::GAMEOVER);

		_pc->PCWaveGameOver();
	}
}

void ASA_GM::ShootPROJ()
{
	/*도착점을 통해 velocity를 계산합니다*/
	//FVector2D v_velocity = USA_FunctionLibrary::GetVelocityByV2(_proj_loc_start_2d, FVector2D(v_dest.X, v_dest.Y));

	ASA_Projectile* spawn_proj = _manager_pool->PoolGetPROJByCode("PROJ00001");
	spawn_proj->PROJInit(GetNewId(), _proj_loc_start_3d, _proj_velocity, 0.f);
	_spawn_projs.Add(spawn_proj);
}

void ASA_GM::ChangePROJVelocity(const FVector& v_dest)
{
	_proj_velocity = USA_FunctionLibrary::GetVelocityByV2(_proj_loc_start_2d, FVector2D(v_dest.X, v_dest.Y));
}

const int64 ASA_GM::GetNewId() { return ++_id_master; }
ASA_SpawnPoint* ASA_GM::GetRandomSpawnPoint() { return _mob_spawn_points[UKismetMathLibrary::RandomInteger(_mob_spawn_points.Num())]; }
const FInfoPlayer& ASA_GM::GetInfoPlayer() const { return _info_player; }
void ASA_GM::SetWaveStatus(const EWaveStatus e_wave_status) { _wave_status = e_wave_status; }