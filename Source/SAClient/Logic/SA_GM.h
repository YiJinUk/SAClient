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
	//1�����Ӹ��� 1�� �����ݴϴ�
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
	//���̺������� �ٽ� Ÿ��Ʋ�� ���ư��ϴ�
	void ReturnTitle();
#pragma endregion

#pragma region Wave
public:
	void WaveStart();
	//���̺����Ḧ üũ�մϴ�
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
	//���͵��� �������Դϴ�
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

	//�߻�ü�� ���۵Ǵ� ��ġ�Դϴ� 3D
	UPROPERTY()
		FVector _proj_loc_start_3d = FVector::ZeroVector;
	//�߻�ü�� ���۵Ǵ� ��ġ�Դϴ� 2D
	UPROPERTY()
		FVector2D _proj_loc_start_2d = FVector2D::ZeroVector;
	//�߻�ü�� velocity�Դϴ�
	UPROPERTY()
		FVector2D _proj_velocity = FVector2D::ZeroVector;
#pragma endregion
};
