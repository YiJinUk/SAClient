// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/SA_GM.h"
#include "SA_FunctionLibrary.h"
#include "SA_GI.h"
#include "SA_PC.h"
#include "Animation/SA_AM.h"
#include "Manager/SA_Manager_Pool.h"
#include "Manager/SA_Manager_Battle.h"
#include "Manager/SA_Manager_VFX.h"
#include "Manager/SA_Manager_SFX.h"
#include "Manager/SA_Manager_SaveLoad.h"
#include "Actor/Unit/Player/SA_Player.h"
#include "Actor/Unit/Monster/SA_Monster.h"
#include "Actor/Object/SA_SpawnPoint.h"
#include "Actor/Object/Projectile/SA_Projectile.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetInternationalizationLibrary.h"

#include "DrawDebugHelpers.h"

void ASA_GM::DebugWaveStart()
{
	WaveStart();
}
void ASA_GM::DebugInitPlayer()
{
	_info_player.SetGem(_data_game_cache->GetPlayetBaseGem());

	_info_player.SetDMG(_data_game_cache->GetPlayerBaseDMG());
	_info_player.SetAS(_data_game_cache->GetPlayerBaseAS());
	_info_player.SetShotNumber(_data_game_cache->GetPlayerBaseShotNum());
	_info_player.SetPenetrate(_data_game_cache->GetPlayerBasePenetrate());

	_info_player.SetUpgradeCostDMG(_data_game_cache->GetUpgradeCostDMG());
	_info_player.SetUpgradeCostAS(_data_game_cache->GetUpgradeCostAS());
	_info_player.SetUpgradeCostShotNumber(_data_game_cache->GetUpgradeCostShotNum());
	_info_player.SetUpgradeCostPenetrate(_data_game_cache->GetUpgradeCostPenetrate());

	_info_wave.InitStruct();

	InitInfoPlayerChr();

	_pc->DebugRefreshTitle();

	GameSave();
}

ASA_GM::ASA_GM()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASA_GM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	/*���� ���ʷ� ������׽��ϴ� �ʱ�ȭ�� �����մϴ�*/
	_pc = Cast<ASA_PC>(NewPlayer);
}

void ASA_GM::BeginPlay()
{
	Super::BeginPlay();

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

	/*�Ŵ����� �����մϴ�*/
	//���� ��ü �����
	FActorSpawnParameters s_param;
	s_param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	_manager_pool = wld->SpawnActor<ASA_Manager_Pool>(s_param); // Ǯ�� �Ŵ���
	_manager_battle = wld->SpawnActor<ASA_Manager_Battle>(s_param); // ���� �Ŵ���
	_manager_vfx = wld->SpawnActor<ASA_Manager_VFX>(s_param); // ���� �Ŵ���
	_manager_sfx = wld->SpawnActor<ASA_Manager_SFX>(s_param); // ���� �Ŵ���
	_manager_saveload = wld->SpawnActor<ASA_Manager_SaveLoad>(s_param); // ���̺�ε� �Ŵ���
	

	/*���׹����� ���� ��� �Ŵ����� �����ϰ� �ѹ��� �ʱ�ȭ�մϴ�*/
	_manager_pool->PoolInit(_sagi);
	_manager_battle->BattleInit(this, _pc, _manager_vfx);
	_manager_sfx->SFXInit(_sagi);
	_manager_vfx->VFXInit(_sagi);

	/*�߻�ü ������ �ʱ�ȭ�մϴ�*/
	_proj_loc_start_3d = FVector(_player_loc.X, _player_loc.Y, _data_game_cache->GetPROJZFixed());
	_proj_loc_start_2d = FVector2D(_player_loc.X, _player_loc.Y);
	_proj_velocity = FVector2D(1.f, 0.f);

	/*������� ���*/
	_manager_sfx->SFXStart(ESFXType::BACKGROUND);

	/*���̺������� �ʱ�ȭ�մϴ�*/
	_info_wave.InitStruct();

	/*�÷��̾��� ���̺굥���͸� �ҷ��ɴϴ�*/
	GameLoad();

	/*�÷��̾ �ʱ�ȭ�մϴ�*/
	_pc->PCInit(this, _info_player_chr);

	/*�÷��̾� �ִϸ��̼��ν��Ͻ� �ʱ�ȭ*/
	_player_am = _player_chr->GetSAAM();
	_player_am->InitSAAM(this);

	/*�ε��� ������ ���� ���带 �ʱ�ȭ�մϴ�*/
	_info_option.is_sfx_on = !_info_option.is_sfx_on;
	SFXToggle();

	/*�� �ʱ�ȭ�մϴ�*/
	SetLanguage(_info_option.language);

	ReturnTitle();
}

void ASA_GM::InitInfoPlayerChr()
{
	/*�÷��̾����� �ʱ�ȭ*/
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

		/*���͸� �����մϴ�*/
		TickSpawnMonster();

		/*�߻�ü �߻� �˻�*/
		TickCheckShootPROJ();

		/*���� �̵� �� ����*/
		TickMoveMonster(DeltaTime);

		/*�߻�ü �̵� �� ����*/
		TickMovePROJ(DeltaTime);

		/*Ʈ����ü��Ʈ�� �����ϴ���*/
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
		ASA_SpawnPoint* spawn_point_rnd = nullptr;
		ASA_Monster* spawn_monster = nullptr;

		if (_info_wave.monster_spawn_count >= 1)
		{
			spawn_monster = _manager_pool->PoolGetMonsterByCode("MOB00001");
			spawn_point_rnd = GetRandomSpawnPoint();
			spawn_monster->MOBInit(GetNewId(), _info_wave.monster_hp, _info_wave.monster_move_speed, spawn_point_rnd);
			--_info_wave.monster_spawn_count;
		}
		else if(_info_wave.monster_split_spawn_count >= 1)
		{
			spawn_monster = _manager_pool->PoolGetMonsterByCode("MOB00002");
			spawn_point_rnd = GetRandomSpawnPoint();
			spawn_monster->MOBInit(GetNewId(), _info_wave.monster_split_hp, _info_wave.monster_move_speed, spawn_point_rnd);
			--_info_wave.monster_split_spawn_count;
		}
		else
		{
			/*��ȯ�Ұ� ����*/
			return;
		}
		
		_spawn_monsters.Add(spawn_monster);
		++_count_spawn_monster_current;
	}
}

void ASA_GM::TickCheckShootPROJ()
{
	++_info_player_chr.as_wait;
	if (_info_player_chr.as_wait >= (60.f / float(_info_player_chr.GetASTotal())) * 60.f)
	{
		/*�߻�*/
		_info_player_chr.as_wait = 0;
		PlayAnimAttack();
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
			--_info_player_chr.hp;

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
		//DrawDebugCircle(GetWorld(), spawn_proj->GetActorLocation(), _data_game_cache->GetPROJRange(), 30, FColor::Red, false, -1.f, 0, 0.f, FVector(1.f, 0.f, 0.f), FVector(0.f, 1.f, 0.f));

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
				/*�̹� ������ �������� Ȯ���մϴ�*/
				//if (spawn_proj->PROJIsAttackedMonsterByMOBId(spawn_monster->GetInfoMonster().id)) continue;

				/*���ݽõ��� ���Ͱ� �׾��ٸ� ���͸� Ǯ���մϴ�*/
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

				/*�߻�ü�� Ǯ�� �����ϴ��� �����մϴ�*/
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
			FDataWave* arr_data_wave_monster = _sagi->FindDataWaveByWaveRound(_info_wave.wave_round);
			for (const FDataWaveMonster& s_data_wave_monster : arr_data_wave_monster->GetSpawnMonsters())
			{
				i_hp_treasure_chest += _info_wave.monster_hp * s_data_wave_monster.GetSpawnCount();
			}
			i_hp_treasure_chest *= 0.5f;
			ASA_Monster* spawn_treasure_chest = _manager_pool->PoolGetMonsterByCode("MOB00010");
			spawn_treasure_chest->MOBInitTreasureChest(GetNewId(), i_hp_treasure_chest, _info_wave.wave_round * 5, _data_game_cache->GetTreasureChestSpawnLoc());
			_spawn_monsters.Add(spawn_treasure_chest);
		}
	}
}

void ASA_GM::TickCheckWaveEnd()
{
	/*�÷��̾��� ü���� 0���Ϸ� �������� ������ ����˴ϴ�*/
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
	_pc->PCUIUpdateWaveRound(_info_wave.wave_round);
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
	_info_wave_clear.InitStruct();
	_info_wave_clear.clear_wave_round = _info_wave.wave_round;

	/*�ش� ���̺꿡�� �����Ǵ� ���������� �����ɴϴ�*/
	FDataWave* s_data_wave = _sagi->FindDataWaveByWaveRound(_info_wave.wave_round);
	if(s_data_wave)
		_data_wave_current = *s_data_wave;
	else
	{
		//Err ������ ���̺굥���Ͱ� �����ϴ�. 1���̺�� ���ư��ϴ�
		_info_wave.wave_round = 1;
		++_info_wave.wave_phase;
		s_data_wave = _sagi->FindDataWaveByWaveRound(_info_wave.wave_round);
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

	/*�ش� ���̺꿡�� ������ ������ ü�°� �̼��� �̸� ���մϴ�*/
	_info_wave.monster_hp = (_data_wave_current.GetMonsterHP() + (_data_wave_current.GetMonsterHP() * _info_wave.wave_phase * 3)) * 2;
	_info_wave.monster_split_hp = _info_wave.monster_hp * 0.7f;
	_info_wave.monster_move_speed = _data_game_cache->GetMonsterBaseMoveSpeed() + _info_wave.wave_round;

	/*�п� ������ ���������� ���̺�´� ������ �������� ������ �̸� ����մϴ�*/
	_count_spawn_monster_max *= 2;
	_info_wave.monster_split_spawn_count = _count_spawn_monster_max * ((float)_info_wave.wave_round * 0.01f);
	_info_wave.monster_spawn_count = _count_spawn_monster_max - _info_wave.monster_split_spawn_count;

	//���̺�
	GameSave();

	InitInfoPlayerChr();

	_pc->PCWaveStart();

	SetWaveStatus(EWaveStatus::PLAY);
}

void ASA_GM::WaveClear()
{
	SetWaveStatus(EWaveStatus::CLEAR);
	++_info_wave.wave_round;
	_pc->PCWaveClear(_info_wave_clear);

	//���̺�
	GameSave();
}

void ASA_GM::WaveGameOver()
{
	GameSave();

	/*���ӿ���*/
	SetWaveStatus(EWaveStatus::GAMEOVER);

	_pc->PCWaveGameOver();
}

void ASA_GM::UpdateInfoWaveClearByGem(const int32 i_gem_obtain)
{
	_info_wave_clear.obtain_gem += i_gem_obtain;
	PlayerChangeStat(EPlayerStat::GEM, i_gem_obtain, true);
}
void ASA_GM::UpdateInfoWaveClearByKillEnemy()
{
	++_info_wave_clear.kill_enemies;
}
void ASA_GM::UpdateInfoWaveClearByScore(const int32 i_score)
{
	_info_wave_clear.score += i_score;
}

void ASA_GM::PlayAnimAttack()
{
	_player_am->Montage_Play(_data_game_cache->GetPlayerAttackMontage());
}
void ASA_GM::ShootPROJ()
{	
	FVector2D v2_proj_velocity;
	for (int32 i = 0; i < _info_player.GetShotNumber(); ++i)
	{
		ASA_Projectile* spawn_proj = _manager_pool->PoolGetPROJByCode("PROJ00001");
		v2_proj_velocity = _proj_velocity.GetRotated(_data_game_cache->GetPROJShotAngle()[i]);
		//spawn_proj->PROJInit(GetNewId(), _proj_loc_start_3d + _data_game_cache->GetPROJShopLoc()[i], _proj_velocity, 0.f);
		spawn_proj->PROJInit(GetNewId(), _proj_loc_start_3d, v2_proj_velocity, USA_FunctionLibrary::GetLookRotatorYawByV3(_proj_loc_start_3d, FVector(v2_proj_velocity.X+ _proj_loc_start_3d.X, v2_proj_velocity.Y+ _proj_loc_start_3d.Y, 0.f)));
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
	//�п������� �������� Ȯ��
	if (!monster_origin->GetInfoMonster().is_split) return;

	const FVector& v_loc_spawn_origin = monster_origin->GetActorLocation();
	FVector v_loc_spawn_new = FVector(v_loc_spawn_origin.X, v_loc_spawn_origin.Y + _data_game_cache->GetMonsterCloneLocY(), 0.f);
	
	for (int32 i = 0; i < 2; ++i)
	{
		ASA_Monster* spawn_monster_new = _manager_pool->PoolGetMonsterByCode("MOB00001");
		if (i == 1)
			v_loc_spawn_new.Y = -v_loc_spawn_new.Y;
		spawn_monster_new->MOBInitClone(GetNewId(), monster_origin->GetInfoMonster().hp_max, v_loc_spawn_new, USA_FunctionLibrary::GetVelocityByV3(v_loc_spawn_new, _player_loc), FRotator(0.f, USA_FunctionLibrary::GetLookRotatorYawByV3(v_loc_spawn_new, _player_loc), 0.f));
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
	_pc->PCUISetCheckBoxSFX(_info_option.is_sfx_on);
	GameSaveOption();
}
void ASA_GM::SetLanguage(const FString& str_code_lang)
{
	if (str_code_lang == "en")
	{
		UKismetInternationalizationLibrary::SetCurrentCulture(str_code_lang);
		_info_option.language = str_code_lang;
		_pc->PCUISetLanguageBtn(false);
	}
	else
	{
		UKismetInternationalizationLibrary::SetCurrentCulture("ko_kr");
		_info_option.language = "ko_kr";
		_pc->PCUISetLanguageBtn(true);
	}

	GameSaveOption();
}

void ASA_GM::UpgradeDMG()
{
	if (_info_player.GetGem() < _data_game_cache->GetUpgradeCostDMG())
	{
		return; // ������ ����
	}

	/*���Ű���*/
	PlayerChangeStat(EPlayerStat::GEM, _info_player.GetUpgradeCostDMG(), false);
	PlayerChangeStat(EPlayerStat::DMG, _data_game_cache->GetUpgradeUnitDMG(), true);
	PlayerIncreaseUpgradeCost(EUpgradeStat::DMG);
}
void ASA_GM::UpgradeAS()
{
	if (_info_player.GetGem() < _info_player.GetUpgradeCostAS())
	{
		return; // ������ ����
	}

	/*���Ű���*/
	PlayerChangeStat(EPlayerStat::GEM, _info_player.GetUpgradeCostAS(), false);
	PlayerChangeStat(EPlayerStat::AS, _data_game_cache->GetUpgradeUnitAS(), true);
	PlayerIncreaseUpgradeCost(EUpgradeStat::AS);
}
void ASA_GM::UpgradeShotNum()
{
	if (_info_player.GetGem() < _info_player.GetUpgradeCostShotNumber())
	{
		return; // ������ ����
	}

	if (_info_player.GetShotNumber() >= _data_game_cache->GetUpgradeMaxShotNum())
	{
		return; // �ִ� ź�˰���
	}

	/*���Ű���*/
	PlayerChangeStat(EPlayerStat::GEM, _info_player.GetUpgradeCostShotNumber(), false);
	PlayerChangeStat(EPlayerStat::SHOT_NUMBER, 1, true);
	PlayerIncreaseUpgradeCost(EUpgradeStat::SHOT_NUMBER);
}
void ASA_GM::UpgradePenetrate()
{
	if (_info_player.GetGem() < _info_player.GetUpgradeCostPenetrate())
	{
		return; // ������ ����
	}

	/*���Ű���*/
	PlayerChangeStat(EPlayerStat::GEM, _info_player.GetUpgradeCostPenetrate(), false);
	PlayerChangeStat(EPlayerStat::PENETRATE, 1, true);
	PlayerIncreaseUpgradeCost(EUpgradeStat::PENETRATE);
}

void ASA_GM::PlayerChangeStat(const EPlayerStat e_player_stat, const int32 i_value, const bool b_is_add)
{
	switch (e_player_stat)
	{
	case EPlayerStat::GEM:
		if (b_is_add)
			_info_player.SetGem(_info_player.GetGem() + i_value);
		else
			_info_player.SetGem(_info_player.GetGem() - i_value);

		_pc->PCUIUpdatePlayerStat(e_player_stat, _info_player.GetGem());
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
void ASA_GM::PlayerIncreaseUpgradeCost(const EUpgradeStat e_upgrade_stat)
{
	switch (e_upgrade_stat)
	{
	case EUpgradeStat::DMG:
		_info_player.SetUpgradeCostDMG(_info_player.GetUpgradeCostDMG() * _data_game_cache->GetUpgradeDMGCostIncrease());
		_pc->PCUIUpdateUpgradeCost(e_upgrade_stat, _info_player.GetUpgradeCostDMG());
		break;
	case EUpgradeStat::AS:
		_info_player.SetUpgradeCostAS(_info_player.GetUpgradeCostAS() * _data_game_cache->GetUpgradeASCostIncrease());
		_pc->PCUIUpdateUpgradeCost(e_upgrade_stat, _info_player.GetUpgradeCostAS());
		break;
	case EUpgradeStat::SHOT_NUMBER:
		_info_player.SetUpgradeCostShotNumber(_info_player.GetUpgradeCostShotNumber() * _data_game_cache->GetUpgradeShotNumCostIncrease());
		_pc->PCUIUpdateUpgradeCost(e_upgrade_stat, _info_player.GetUpgradeCostShotNumber());
		break;
	case EUpgradeStat::PENETRATE:
		_info_player.SetUpgradeCostPenetrate(_info_player.GetUpgradeCostPenetrate() * _data_game_cache->GetUpgradePenetrateCostIncrease());
		_pc->PCUIUpdateUpgradeCost(e_upgrade_stat, _info_player.GetUpgradeCostPenetrate());
		break;
	default:
		return;
		break;
	}
}

void ASA_GM::GameSave()
{
	_manager_saveload->SaveStart(_info_player, _info_wave.wave_round);
}
void ASA_GM::GameSaveOption()
{
	_manager_saveload->SaveOptionStart(_info_option);
}
void ASA_GM::GameLoad()
{
	_manager_saveload->ReadStart(_info_player, _info_wave.wave_round, _info_option);
}

const int64 ASA_GM::GetNewId() { return ++_id_master; }
ASA_SpawnPoint* ASA_GM::GetRandomSpawnPoint() { return _mob_spawn_points[UKismetMathLibrary::RandomInteger(_mob_spawn_points.Num())]; }
const FInfoPlayerCharacter& ASA_GM::GetInfoPlayerChr() const { return _info_player_chr; }
const FInfoPlayer& ASA_GM::GetInfoPlayer() const { return _info_player; }
void ASA_GM::SetWaveStatus(const EWaveStatus e_wave_status) { _wave_status = e_wave_status; }
const int32 ASA_GM::GetWaveRoundCurrent() const { return _info_wave.wave_round; }
