// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/SA_GM.h"
#include "SA_FunctionLibrary.h"
#include "SA_GI.h"
#include "SA_PC.h"
#include "Manager/SA_Manager_Pool.h"
#include "Actor/Unit/Player/SA_Player.h"
#include "Actor/Unit/Monster/SA_Monster.h"
#include "Actor/Object/SA_SpawnPoint.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void ASA_GM::DebugWaveStart()
{
	WaveStart();
}

void ASA_GM::PostLogin(APlayerController* NewPlayer)
{
	/*���� ���ʷ� ������׽��ϴ� �ʱ�ȭ�� �����մϴ�*/
	_pc = Cast<ASA_PC>(NewPlayer);

	GMInit();
}

void ASA_GM::GMInit()
{
	UWorld* wld = GetWorld();
	_sagi = wld->GetGameInstance<USA_GI>();
	if (!_sagi) //Err
	{
		//�����ν��Ͻ��� �ҷ��� �� �����ϴ�
	}

	/*�����ν��Ͻ� �ʱ�ȭ*/
	_sagi->GIInit();

	/*���� ����ϴ� ���ӵ����͸� ĳ���մϴ�*/
	_data_game_cache = _sagi->GetDataGame();

	/*�÷��̾����� �ʱ�ȭ*/
	_info_player.hp = _data_game_cache->GetPlayetHP();

	/*�ʿ� ������ �÷��̾ �����ɴϴ�*/
	TArray<AActor*> arr_found_actor;
	UGameplayStatics::GetAllActorsOfClass(wld, ASA_Player::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1)
	{
		_player_chr = Cast<ASA_Player>(arr_found_actor[0]);
		if (!_player_chr) // Err
		{
			//�÷��̾� ĳ���͸� ã�� �� �����ϴ�
		}
		_player_loc = _player_chr->GetActorLocation();
	}

	/*�ʿ� ������ ���� ��������Ʈ�� �����ɴϴ�*/
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

	/*�Ŵ����� ���� �Ǵ� �������� �����ɴϴ�*/
	//Ǯ�� �Ŵ���
	UGameplayStatics::GetAllActorsOfClass(wld, ASA_Manager_Pool::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1)
		_manager_pool = Cast<ASA_Manager_Pool>(arr_found_actor[0]);

	/*���׹����� ���� ��� �Ŵ����� �����ϰ� �ѹ��� �ʱ�ȭ�մϴ�*/
	_manager_pool->PoolInit();

	//���� ��ü �����
	//FActorSpawnParameters s_param;
	//s_param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//_manager_pool = wld->SpawnActor<ASA_Manager_Pool>(s_param); // Ǯ�� �Ŵ���

	/*�÷��̾ �ʱ�ȭ�մϴ�*/
	_pc->PCInit(this, _info_player);
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
			for (int32 i = 0; i < 10; ++i)
			{
				spawn_point_rnd = GetRandomSpawnPoint();
				spawn_monster = _manager_pool->PoolGetMonsterByCode("MOB00001");
				spawn_monster->MOBInit(GetNewId(), spawn_point_rnd->GetPointSpawnLocation(), spawn_point_rnd->GetPointVelocity(), spawn_point_rnd->GetPointRotator());
				_spawn_monsters.Add(spawn_monster);
			}
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

		/*UI Update*/
		_pc->PCUIUpdateCheck();
	}
}

void ASA_GM::WaveStart()
{
	_tick = 0;
	SetWaveStatus(EWaveStatus::PLAY);
}

const int64 ASA_GM::GetNewId() { return ++_id_master; }
ASA_SpawnPoint* ASA_GM::GetRandomSpawnPoint() { return _mob_spawn_points[UKismetMathLibrary::RandomInteger(_mob_spawn_points.Num())]; }
const FInfoPlayer& ASA_GM::GetInfoPlayer() const { return _info_player; }
void ASA_GM::SetWaveStatus(const EWaveStatus e_wave_status) { _wave_status = e_wave_status; }