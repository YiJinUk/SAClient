// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "GameFramework/GameModeBase.h"
#include "SA_GM.generated.h"

class USA_AM;
class USA_GI;
class ASA_PC;
class ASA_Player;
class ASA_Monster;
class ASA_SpawnPoint;
class ASA_Manager_Pool;
class ASA_Manager_Battle;
class ASA_Manager_VFX;
class ASA_Manager_SFX;
class ASA_Manager_SaveLoad;

/**
 * 
 */
UCLASS()
class SACLIENT_API ASA_GM : public AGameModeBase
{
	GENERATED_BODY()

#pragma region Debug
public:
	UFUNCTION(BlueprintCallable)
		void DebugWaveStart();
	UFUNCTION(BlueprintCallable)
		void DebugInitPlayer();
#pragma endregion

#pragma region General
private:
	FORCEINLINE const int64 GetNewId();
private:
	UPROPERTY()
		int64 _id_master = 0;
	//1프레임마다 1씩 더해줍니다
	UPROPERTY()
		int64 _tick = 0;

	UPROPERTY()
		USA_GI* _sagi = nullptr;

	FDataGame* _data_game_cache = nullptr;
#pragma endregion

#pragma region Init
protected:
	ASA_GM();
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void BeginPlay() override;
private:
	void GMInit();
#pragma endregion

#pragma region Tick
protected:
	virtual void Tick(float DeltaTime) override;
private:
	void TickSpawnMonster();
	void TickCheckShootPROJ();
	void TickMoveMonster(const float f_delta_time);
	void TickMovePROJ(const float f_delta_time);
	void TickCheckSpawnTreasuerChest();
	//웨이브종료를 체크합니다
	void TickCheckWaveEnd();
#pragma endregion

#pragma region Manager
private:
	UPROPERTY()
		ASA_Manager_Pool* _manager_pool = nullptr;
	UPROPERTY()
		ASA_Manager_Battle* _manager_battle = nullptr;
	UPROPERTY()
		ASA_Manager_VFX* _manager_vfx = nullptr;
	UPROPERTY()
		ASA_Manager_SFX* _manager_sfx = nullptr;
	UPROPERTY()
		ASA_Manager_SaveLoad* _manager_saveload = nullptr;
#pragma endregion

#pragma region Game
public:
	//웨이브종료후 다시 타이틀로 돌아갑니다
	void ReturnTitle();
#pragma endregion

#pragma region Wave
public:
	void WaveStart();
	void WaveClear();
	void WaveGameOver();

	void UpdateInfoWaveClearByGold(const int32 i_gold_obtain);
	void UpdateInfoWaveClearByGem(const int32 i_gem_obtain);
	void UpdateInfoWaveClearByKillEnemy();
	void UpdateInfoWaveClearByScore(const int32 i_score);

	FORCEINLINE void SetWaveStatus(const EWaveStatus e_wave_status);
	const int32 GetWaveRoundCurrent() const;
private:
	UPROPERTY()
		EWaveStatus _wave_status = EWaveStatus::TITLE;
	UPROPERTY()
		int32 _wave_round_current = 1;
	//웨이브중 몬스터가 생성된 횟수입니다
	UPROPERTY()
		int32 _count_spawn_monster_current = 0;
	//현재웨이브에서 생성되야할 몬스터의 총 개수입니다
	UPROPERTY()
		int32 _count_spawn_monster_max = 0;
	// T : 트레져체스트를 부셨거나, 부시지못한채로 클리어 했습니다
	UPROPERTY()
		bool _is_death_treasure_chest = false;

	//새로 복제해서 사용하기 때문에 내용을 변경해도 상관없습니다
	UPROPERTY()
		FDataWave _data_wave_current;
	//웨이브클리어정보 입니다
	UPROPERTY()
		FInfoWaveClear _info_wave_clear;
#pragma endregion

#pragma region PlayerChr
public:
	void InitInfoPlayerChr();
	const FInfoPlayerCharacter& GetInfoPlayerChr() const;
private:
	void PlayAnimAttack();
private:
	UPROPERTY()
		ASA_PC* _pc = nullptr;
	UPROPERTY()
		ASA_Player* _player_chr = nullptr;
	UPROPERTY()
		USA_AM* _player_am = nullptr;
	//몬스터들의 도착점입니다
	UPROPERTY()
		FVector _player_loc = FVector::ZeroVector;

	UPROPERTY()
		FInfoPlayerCharacter _info_player_chr;
#pragma endregion

#pragma region Monster
private:
	void SpawnMonsterClone(ASA_Monster* monster_origin);
	void PoolInAllSpawnedMonsters();

	ASA_SpawnPoint* GetRandomSpawnPoint();
private:
	UPROPERTY()
		TArray<ASA_Monster*> _spawn_monsters;
	UPROPERTY()
		TArray<ASA_SpawnPoint*> _mob_spawn_points;
#pragma endregion

#pragma region Projectile
public:
	void ShootPROJ();
	void ChangePROJVelocity(const FVector& v_dest);

	void PoolInAllSpawnedPROJs();
private:
	UPROPERTY()
		TArray<ASA_Projectile*> _spawn_projs;

	//발사체가 시작되는 위치입니다 3D
	UPROPERTY()
		FVector _proj_loc_start_3d = FVector::ZeroVector;
	//발사체가 시작되는 위치입니다 2D
	UPROPERTY()
		FVector2D _proj_loc_start_2d = FVector2D::ZeroVector;
	//발사체의 velocity입니다
	UPROPERTY()
		FVector2D _proj_velocity = FVector2D::ZeroVector;
#pragma endregion

#pragma region Upgrade
public:
	void UpgradeDMG(const int32 i_cost);
	void UpgradeAS();
	void UpgradeShotNum();
	void UpgradePenetrate();
#pragma endregion

#pragma region Player
public:
	void PlayerChangeStat(const EPlayerStat e_player_stat, const int32 i_value, const bool b_is_add);
	void PlayerIncreaseUpgradeCost(const EUpgradeStat e_upgrade_stat);

	const FInfoPlayer& GetInfoPlayer() const;
private:
	UPROPERTY()
		FInfoPlayer _info_player;
#pragma endregion

#pragma region SFX
public:
	void SFXToggle();
protected:
	UFUNCTION(BlueprintImplementableEvent)
		void BPSFXToggle(const bool b_is_sfx_on);
#pragma endregion

#pragma region Option
private:
	FInfoOption _info_option;
#pragma endregion

#pragma region SaveLoad
private:
	void GameSave();
	void GameSaveOption();

	void GameLoad();
#pragma endregion
};
