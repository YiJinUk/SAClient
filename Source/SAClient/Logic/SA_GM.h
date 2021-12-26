// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "GameFramework/GameModeBase.h"
#include "SA_GM.generated.h"

class USA_GI;
class ASA_PC;
class ASA_Player;
class ASA_Monster;
class ASA_SpawnPoint;
class ASA_Manager_Pool;
class ASA_Manager_Battle;

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
	virtual void PostLogin(APlayerController* NewPlayer) override;
private:
	void GMInit();
#pragma endregion

#pragma region Tick
protected:
	virtual void Tick(float DeltaTime) override;
#pragma endregion

#pragma region Manager
private:
	UPROPERTY()
		ASA_Manager_Pool* _manager_pool = nullptr;
	UPROPERTY()
		ASA_Manager_Battle* _manager_battle = nullptr;
#pragma endregion

#pragma region Game
public:
	//웨이브종료후 다시 타이틀로 돌아갑니다
	void ReturnTitle();
#pragma endregion

#pragma region Wave
public:
	void WaveStart();
	//웨이브종료를 체크합니다
	void WaveEndCheck();

	FORCEINLINE void SetWaveStatus(const EWaveStatus e_wave_status);
private:
	EWaveStatus _wave_status = EWaveStatus::TITLE;
#pragma endregion

#pragma region Player
public:
	void InitInfoPlayer();
	FORCEINLINE const FInfoPlayer& GetInfoPlayer() const;
private:
	UPROPERTY()
		ASA_PC* _pc = nullptr;
	UPROPERTY()
		ASA_Player* _player_chr = nullptr;
	//몬스터들의 도착점입니다
	UPROPERTY()
		FVector _player_loc = FVector::ZeroVector;

	UPROPERTY()
		FInfoPlayer _info_player;
#pragma endregion

#pragma region Monster
private:
	FORCEINLINE ASA_SpawnPoint* GetRandomSpawnPoint();
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
};
