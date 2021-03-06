// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Runtime/CoreUObject/Public/Templates/SubclassOf.h"
#include "UObject/NoExportTypes.h"
#include "SA_SharedStruct.generated.h"

class ASA_Monster;
class ASA_Projectile;
class USoundBase;
class UParticleSystem;
class UAnimMontage;

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_SharedStruct : public UObject
{
	GENERATED_BODY()
	
};

UENUM()
enum class ELanguage : uint8
{
	KOREAN,
	ENGLISH,
};

UENUM()
enum class EWaveStatus : uint8
{
	TITLE, // 게임시작전 UI화면 입니다
	PLAY, // 웨이브중
	CLEAR, // 웨이브클리어
	GAMEOVER, // 게임오버
};

UENUM()
enum class EPlayerStat : uint8
{
	GEM,
	DMG,
	AS,
	SHOT_NUMBER,
	PENETRATE,
};

UENUM()
enum class EUpgradeStat : uint8
{
	DMG,
	AS,
	SHOT_NUMBER,
	PENETRATE,
};

UENUM()
enum class EMonsterType : uint8
{
	MONSTER_BASE,
	MONSTER_SPLIT,
	TREASURE_CHEST,
};

UENUM()
enum class EVFXType : uint8
{
	PROJ_HIT,
};

UENUM()
enum class ESFXType : uint8
{
	BACKGROUND,
	PROJ_SHOT,
	PROJ_HIT,
};

UENUM()
enum class EUIMainStatus : uint8
{
	TITLE,
	GAME,
};


USTRUCT()
struct FInfoOption
{
	GENERATED_BODY()

public:
	UPROPERTY()
		bool is_sfx_on = true;

	UPROPERTY()
		FString language = "0";

};

USTRUCT(BlueprintType)
struct FDataGame : public FTableRowBase
{
	GENERATED_BODY()
protected:
	//목표지점 반경입니다
	UPROPERTY(EditAnywhere, Category = "Wave")
		int16 _dest_radius = 100;
	UPROPERTY(EditAnywhere, Category = "Wave")
		FVector _treasure_chest_spawn_loc = FVector(-1500.f, 0.f, 0.f);
	UPROPERTY(EditAnywhere, Category = "Wave")
		int32 _hp_rate_phase = 0;
	UPROPERTY(EditAnywhere, Category = "Wave")
		int32 _add_monster_move_speed = 1;
	UPROPERTY(EditAnywhere, Category = "Wave")
		int32 _add_monster_spawn_count = 3;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		int16 _proj_speed = 1000;
	UPROPERTY(EditAnywhere, Category = "Projectile")
		int16 _proj_range = 100;
	UPROPERTY(EditAnywhere, Category = "Projectile")
		int8 _proj_z_fixed = 50;
	/*탄알 발사시 탄알의 각도 입니다 해당 값은 기본velocity값에서 각도를 구한후 사용합니다*/
	UPROPERTY(EditAnywhere, Category = "Projectile")
		TArray<int16> _proj_shot_angle;
	UPROPERTY(EditAnywhere, Category = "Projectile")
		int8 _proj_max_shot_number = 7;

	UPROPERTY(EditAnywhere, Category = "Player")
		int16 _player_hp = 100;
	UPROPERTY(EditAnywhere, Category = "Player")
		int32 _player_base_gem = 10;
	UPROPERTY(EditAnywhere, Category = "Player")
		int32 _player_base_dmg = 1;
	UPROPERTY(EditAnywhere, Category = "Player")
		int32 _player_base_as = 60;
	UPROPERTY(EditAnywhere, Category = "Player")
		int8 _player_base_shot_num = 1;
	UPROPERTY(EditAnywhere, Category = "Player")
		int8 _player_base_penetrate = 1;
	UPROPERTY(EditAnywhere, Category = "Player")
		UAnimMontage* _player_attack_montage = nullptr;

	UPROPERTY(EditAnywhere, Category = "Monster")
		int8 _monster_clone_loc_y = 100;
	UPROPERTY(EditAnywhere, Category = "Monster")
		int32 _monster_base_move_speed = 200;

	UPROPERTY(EditAnywhere, Category = "UpgradeUnit")
		int32 _upgrade_unit_dmg = 1;
	UPROPERTY(EditAnywhere, Category = "UpgradeUnit")
		int32 _upgrade_unit_as = 6;

	UPROPERTY(EditAnywhere, Category = "UpgradeCost")
		int32 _upgrade_cost_dmg = 1;
	UPROPERTY(EditAnywhere, Category = "UpgradeCost")
		int32 _upgrade_cost_as = 10;
	UPROPERTY(EditAnywhere, Category = "UpgradeCost")
		int32 _upgrade_cost_shot_num = 10;
	UPROPERTY(EditAnywhere, Category = "UpgradeCost")
		int32 _upgrade_cost_penetrate = 10;
	//UPROPERTY(EditAnywhere, Category = "UpgradeCost")
	//	float _upgrade_dmg_cost_increase = 1.1;
	UPROPERTY(EditAnywhere, Category = "UpgradeCost")
		int32 _upgrade_dmg_cost_increase = 5;
	UPROPERTY(EditAnywhere, Category = "UpgradeCost")
		float _upgrade_as_cost_increase = 1.5;
	UPROPERTY(EditAnywhere, Category = "UpgradeCost")
		float _upgrade_shot_num_cost_increase = 1.5;
	UPROPERTY(EditAnywhere, Category = "UpgradeCost")
		float _upgrade_penetrate_cost_increase = 1.5;

	UPROPERTY(EditAnywhere, Category = "UpgradeMax")
		int32 _upgrade_max_as = 3000;
	UPROPERTY(EditAnywhere, Category = "UpgradeMax")
		int32 _upgrade_max_shot_num = 7;
public:
	FORCEINLINE const int16 GetDestRadius() const { return _dest_radius; }
	FORCEINLINE const FVector GetTreasureChestSpawnLoc() const { return _treasure_chest_spawn_loc; }
	FORCEINLINE const int32 GetHPRatePhase() const { return _hp_rate_phase; }
	FORCEINLINE const int32 GetAddMonsterMoveSpeed() const { return _add_monster_move_speed; }
	FORCEINLINE const int32 GetAddMonsterSpawnCount() const { return _add_monster_spawn_count; }

	FORCEINLINE const int16 GetPROJSpeed() const { return _proj_speed; }
	FORCEINLINE const int16 GetPROJRange() const { return _proj_range; }
	FORCEINLINE const int8 GetPROJZFixed() const { return _proj_z_fixed; }
	FORCEINLINE const TArray<int16>& GetPROJShotAngle() const { return _proj_shot_angle; }
	FORCEINLINE const int8 GetPROJMaxShotNumber() const { return _proj_max_shot_number; }

	FORCEINLINE UAnimMontage* GetPlayerAttackMontage() { return _player_attack_montage; }
	FORCEINLINE const int16 GetPlayetHP() const { return _player_hp; }
	FORCEINLINE const int32 GetPlayetBaseGem() const { return _player_base_gem; }
	FORCEINLINE const int32 GetPlayerBaseDMG() const { return _player_base_dmg; }
	FORCEINLINE const int32 GetPlayerBaseAS() const { return _player_base_as; }
	FORCEINLINE const int32 GetPlayerBaseShotNum() const { return _player_base_shot_num; }
	FORCEINLINE const int32 GetPlayerBasePenetrate() const { return _player_base_penetrate; }

	FORCEINLINE const int8 GetMonsterCloneLocY() const { return _monster_clone_loc_y; }
	FORCEINLINE const int32 GetMonsterBaseMoveSpeed() const { return _monster_base_move_speed; }

	FORCEINLINE const int32 GetUpgradeUnitDMG() const { return _upgrade_unit_dmg; }
	FORCEINLINE const int32 GetUpgradeUnitAS() const { return _upgrade_unit_as; }

	FORCEINLINE const int32 GetUpgradeCostDMG() const { return _upgrade_cost_dmg; }
	FORCEINLINE const int32 GetUpgradeCostAS() const { return _upgrade_cost_as; }
	FORCEINLINE const int32 GetUpgradeCostShotNum() const { return _upgrade_cost_shot_num; }
	FORCEINLINE const int32 GetUpgradeCostPenetrate() const { return _upgrade_cost_penetrate; }
	FORCEINLINE const int32 GetUpgradeDMGCostIncrease() const { return _upgrade_dmg_cost_increase; }
	FORCEINLINE const float GetUpgradeASCostIncrease() const { return _upgrade_as_cost_increase; }
	FORCEINLINE const float GetUpgradeShotNumCostIncrease() const { return _upgrade_shot_num_cost_increase; }
	FORCEINLINE const float GetUpgradePenetrateCostIncrease() const { return _upgrade_penetrate_cost_increase; }

	FORCEINLINE const int32 GetUpgradeMaxAS() const { return _upgrade_max_as; }
	FORCEINLINE const int32 GetUpgradeMaxShotNum() const { return _upgrade_max_shot_num; }
};

USTRUCT(BlueprintType)
struct FDataVFX : public FTableRowBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "Projectile")
		UParticleSystem* _proj_hit = nullptr;

public:
	FORCEINLINE UParticleSystem* GetPROJHit() const { return _proj_hit; }
};

USTRUCT(BlueprintType)
struct FDataSFX : public FTableRowBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "Level")
		USoundBase* _backgound = nullptr;
	UPROPERTY(EditAnywhere, Category = "Projectile")
		USoundBase* _proj_shot = nullptr;
	UPROPERTY(EditAnywhere, Category = "Projectile")
		USoundBase* _proj_hit = nullptr;

public:
	FORCEINLINE USoundBase* GetBackGround() const { return _backgound; }
	FORCEINLINE USoundBase* GetPROJShot() const { return _proj_shot; }
	FORCEINLINE USoundBase* GetPROJHit() const { return _proj_hit; }
};

USTRUCT(BlueprintType)
struct FDataWaveMonster
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "General")
		FString _code_monster = "0";

public:
	FORCEINLINE const FString& GetCodeMonster() const { return _code_monster; }
};

USTRUCT(BlueprintType)
struct FDataWave
{
	GENERATED_BODY()
protected:
	//해당 틱 마다 몬스터를 생성합니다
	UPROPERTY(EditAnywhere, Category = "General")
		int16 _spawn_tick_interval = 12;
	UPROPERTY(EditAnywhere, Category = "General")
		int32 _mob_hp = 0;
	UPROPERTY(EditAnywhere, Category = "General")
		int32 _spawn_count = 0;
	//UPROPERTY(EditAnywhere, Category = "General")
		//TArray<FDataWaveMonster> _spawn_monsters;
public:
	FORCEINLINE const int16 GetSpawnTickInterval() const { return _spawn_tick_interval; }
	FORCEINLINE const int32 GetMonsterHP() const { return _mob_hp; }
	FORCEINLINE const int32 GetSpawnCount() const { return _spawn_count; }
	//FORCEINLINE TArray<FDataWaveMonster>& GetSpawnMonsters() { return _spawn_monsters; }
};

USTRUCT(BlueprintType)
struct FDataWaves : public FTableRowBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "General")
		TArray<FDataWave> _waves;
public:
	FORCEINLINE TArray<FDataWave>& GetWaves() { return _waves; }
};

USTRUCT()
struct FInfoPlayer
{
	GENERATED_BODY()

private:
	UPROPERTY()
		int32 _gem = 0;

	UPROPERTY()
		int32 _dmg = 1;
	UPROPERTY()
		int32 _as = 60;
	UPROPERTY()
		int8 _shot_number = 1;
	/*
	* 관통샷
	* 해당 값이 1이면 한마리를 관통해서 총 두마리를 공격할 수 있는게 아니라
	* 해당 값만큼 공격이 가능하다는 뜻 입니다
	* 해당값이 5라면 최대5마리를 공격하고 실제 관통은 4번 합니다. 
	*/
	UPROPERTY()
		int8 _penetrate = 0;

	UPROPERTY()
		int32 _upgrade_cost_dmg = 1;
	UPROPERTY()
		int32 _upgrade_cost_as = 1;
	UPROPERTY()
		int32 _upgrade_cost_shot_num = 1;
	UPROPERTY()
		int32 _upgrade_cost_penetrate = 1;
public:
	FORCEINLINE const int32 GetGem() const { return _gem; }

	FORCEINLINE const int32 GetDMG() const { return _dmg; }
	FORCEINLINE const int32 GetAS() const { return _as; }
	FORCEINLINE const int8 GetShotNumber() const { return _shot_number; }
	FORCEINLINE const int8 GetPenetrate() const { return _penetrate; }

	FORCEINLINE const int32 GetUpgradeCostDMG() const { return _upgrade_cost_dmg; }
	FORCEINLINE const int32 GetUpgradeCostAS() const { return _upgrade_cost_as; }
	FORCEINLINE const int32 GetUpgradeCostShotNumber() const { return _upgrade_cost_shot_num; }
	FORCEINLINE const int32 GetUpgradeCostPenetrate() const { return _upgrade_cost_penetrate; }

	FORCEINLINE void SetGem(const int32 i_gem) { _gem = i_gem; }

	FORCEINLINE void SetDMG(const int32 i_dmg) { _dmg = i_dmg; }
	FORCEINLINE void SetAS(const int32 i_as) { _as = i_as; }
	FORCEINLINE void SetShotNumber(const int8 i_shot_number) { _shot_number = i_shot_number; }
	FORCEINLINE void SetPenetrate(const int8 i_penetrate) { _penetrate = i_penetrate; }

	FORCEINLINE void SetUpgradeCostDMG(const int32 i_upgrade_cost_dmg) { _upgrade_cost_dmg = i_upgrade_cost_dmg; }
	FORCEINLINE void SetUpgradeCostAS(const int32 i_upgrade_cost_as) { _upgrade_cost_as = i_upgrade_cost_as; }
	FORCEINLINE void SetUpgradeCostShotNumber(const int32 i_upgrade_cost_shot_number) { _upgrade_cost_shot_num = i_upgrade_cost_shot_number; }
	FORCEINLINE void SetUpgradeCostPenetrate(const int32 i_upgrade_cost_penetrate) { _upgrade_cost_penetrate = i_upgrade_cost_penetrate; }
};

USTRUCT()
struct FInfoPlayerCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY()
		int32 hp = 0;
	UPROPERTY()
		int32 dmg = 0;

	UPROPERTY()
		int32 as = 0;
	UPROPERTY()
		int32 as_wait = 0;
public:
	FORCEINLINE const int32 GetDMGTotal() const { return dmg; }
	FORCEINLINE const int32 GetASTotal() const { return as; }
};

USTRUCT(BlueprintType)
struct FDataMonster : public FTableRowBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
		TSubclassOf<ASA_Monster> _class_monster;
	UPROPERTY(EditAnywhere, Category = "General")
		FString _code = "0";
	UPROPERTY(EditAnywhere, Category = "General")
		EMonsterType _monster_type = EMonsterType::MONSTER_BASE;
public:
	FORCEINLINE const TSubclassOf<ASA_Monster>& GetClassMonster() const { return _class_monster; }
	FORCEINLINE const FString& GetCode() const { return _code; }
	FORCEINLINE const EMonsterType GetMonsterType() const { return _monster_type; }
};

USTRUCT()
struct FInfoMonster
{
	GENERATED_BODY()

public:
	UPROPERTY()
		int64 id = 0;
	UPROPERTY()
		FString code = "0";
	UPROPERTY()
		EMonsterType monster_type = EMonsterType::MONSTER_BASE;

	UPROPERTY()
		FVector velocity = FVector::ZeroVector;
	UPROPERTY()
		FRotator rot = FRotator::ZeroRotator;

	UPROPERTY()
		int32 mob_hp = 0;
	UPROPERTY()
		int32 hp = 0;
	UPROPERTY()
		int32 hp_max = 0;
};

USTRUCT(BlueprintType)
struct FDataProjectile : public FTableRowBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
		TSubclassOf<ASA_Projectile> _class_projectile;
	UPROPERTY(EditAnywhere, Category = "General")
		FString _code = "0";
public:
	FORCEINLINE const TSubclassOf<ASA_Projectile>& GetClassPROJ() const { return _class_projectile; }
	FORCEINLINE const FString& GetCode() const { return _code; }
};

USTRUCT()
struct FInfoProjectile
{
	GENERATED_BODY()

public:
	UPROPERTY()
		int64 id = 0;
	UPROPERTY()
		FString code = "0";

	UPROPERTY()
		FVector velocity = FVector::ZeroVector;

	UPROPERTY()
		int8 penetrate_current = 0;
};

USTRUCT()
struct FInfoWave
{
	GENERATED_BODY()

public:
	UPROPERTY()
		int32 wave_round = 1;
	UPROPERTY()
		int32 wave_phase = 0;
	UPROPERTY()
		int32 monster_hp = 0;
	UPROPERTY()
		int32 monster_split_hp = 0;
	UPROPERTY()
		int32 monster_move_speed = 0;

	UPROPERTY()
		int32 monster_spawn_count_max = 0;
	UPROPERTY()
		int32 monster_spawn_count = 0;
	UPROPERTY()
		int32 monster_split_spawn_count = 0;

	UPROPERTY()
		int32 monster_drop_gem = 0;
	UPROPERTY()
		int32 monster_split_drop_gem = 0;
	UPROPERTY()
		int32 treasure_chest_drop_gem = 0;

public:
	void InitStruct()
	{
		wave_round = 1;
		wave_phase = 0;
		monster_hp = 0;
		monster_split_hp = 0;
		monster_move_speed = 0;

		monster_spawn_count_max = 0;
		monster_spawn_count = 0;
		monster_split_spawn_count = 0;

		monster_drop_gem = 0;
		monster_split_drop_gem = 0;
		treasure_chest_drop_gem = 0;
	}
};

USTRUCT()
struct FInfoWaveClear
{
	GENERATED_BODY()

public:
	UPROPERTY()
		int32 clear_wave_round = 0;
	UPROPERTY()
		int32 obtain_gem = 0;
	UPROPERTY()
		int32 kill_enemies = 0;
	UPROPERTY()
		int32 score = 0;

public:
	void InitStruct()
	{
		clear_wave_round = 0;
		obtain_gem = 0;
		kill_enemies = 0;
		score = 0;
	}
};