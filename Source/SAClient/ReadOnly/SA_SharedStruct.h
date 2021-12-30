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
	GOLD,
	GEM,
	DMG,
	AS,
	SHOT_NUMBER,
	PENETRATE,
};

UENUM()
enum class EMonsterHP : uint8
{
	HP_NO,
	HP_2,
	HP_4,
	HP_8,
	HP_16,
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

	UPROPERTY(EditAnywhere, Category = "Projectile")
		int16 _proj_speed = 1000;
	UPROPERTY(EditAnywhere, Category = "Projectile")
		int16 _proj_range = 100;
	UPROPERTY(EditAnywhere, Category = "Projectile")
		int8 _proj_z_fixed = 50;
	/*탄알 발사시 탄알의 위치값 입니다 해당 값은 베이스위치값에 더해서 사용합니다*/
	UPROPERTY(EditAnywhere, Category = "Projectile")
		TArray<FVector> _proj_shot_loc;
	UPROPERTY(EditAnywhere, Category = "Projectile")
		int8 _proj_max_shot_number = 7;

	UPROPERTY(EditAnywhere, Category = "Player")
		int16 _player_hp = 100;
	UPROPERTY(EditAnywhere, Category = "Player")
		int32 _player_base_dmg = 1;
	UPROPERTY(EditAnywhere, Category = "Player")
		int32 _player_base_as = 60;
	UPROPERTY(EditAnywhere, Category = "Player")
		int8 _player_base_shot_num = 1;
	UPROPERTY(EditAnywhere, Category = "Player")
		int8 _player_base_penetrate = 1;

	UPROPERTY(EditAnywhere, Category = "Monster")
		int8 _monster_clone_loc_y = 100;
public:
	FORCEINLINE const int16 GetDestRadius() const { return _dest_radius; }
	FORCEINLINE const FVector GetTreasureChestSpawnLoc() const { return _treasure_chest_spawn_loc; }

	FORCEINLINE const int16 GetPROJSpeed() const { return _proj_speed; }
	FORCEINLINE const int16 GetPROJRange() const { return _proj_range; }
	FORCEINLINE const int8 GetPROJZFixed() const { return _proj_z_fixed; }
	FORCEINLINE const TArray<FVector>& GetPROJShopLoc() const { return _proj_shot_loc; }
	FORCEINLINE const int8 GetPROJMaxShotNumber() const { return _proj_max_shot_number; }

	FORCEINLINE const int16 GetPlayetHP() const { return _player_hp; }
	FORCEINLINE const int32 GetPlayerBaseDMG() const { return _player_base_dmg; }
	FORCEINLINE const int32 GetPlayerBaseAS() const { return _player_base_as; }
	FORCEINLINE const int32 GetPlayerBaseShotNum() const { return _player_base_shot_num; }
	FORCEINLINE const int32 GetPlayerBasePenetrate() const { return _player_base_penetrate; }

	FORCEINLINE const int8 GetMonsterCloneLocY() const { return _monster_clone_loc_y; }
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
	UPROPERTY(EditAnywhere, Category = "General")
		int32 _spawn_count = 0;
	UPROPERTY(EditAnywhere, Category = "General")
		EMonsterHP _mob_hp = EMonsterHP::HP_2;
public:
	FORCEINLINE const FString& GetCodeMonster() const { return _code_monster; }
	FORCEINLINE const int32 GetSpawnCount() const { return _spawn_count; }
	FORCEINLINE const EMonsterHP GetMonsterHP() const { return _mob_hp; }

	/*게임모드에서 복제한 웨이브데이터에서만 호출합니다*/
	FORCEINLINE void SubSpawnCount() { --_spawn_count; }
};

USTRUCT(BlueprintType)
struct FDataWave
{
	GENERATED_BODY()
protected:
	//한 틱에 생성될 수 있는 최대 값 입니다
	UPROPERTY(EditAnywhere, Category = "General")
		int16 _max_spawn_on_1_tick = 1;
	//해당 틱 마다 몬스터를 생성합니다
	UPROPERTY(EditAnywhere, Category = "General")
		int16 _spawn_tick_interval = 12;
	UPROPERTY(EditAnywhere, Category = "General")
		TArray<FDataWaveMonster> _spawn_monsters;
public:
	FORCEINLINE const int16 GetMaxSpawnOn1Tick() const { return _max_spawn_on_1_tick; }
	FORCEINLINE const int16 GetSpawnTickInterval() const { return _spawn_tick_interval; }
	FORCEINLINE TArray<FDataWaveMonster>& GetSpawnMonsters() { return _spawn_monsters; }
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
		int32 _gold = 0;
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
public:
	FORCEINLINE const int32 GetGold() const { return _gold; }
	FORCEINLINE const int32 GetGem() const { return _gem; }

	FORCEINLINE const int32 GetDMG() const { return _dmg; }
	FORCEINLINE const int32 GetAS() const { return _as; }
	FORCEINLINE const int8 GetShotNumber() const { return _shot_number; }
	FORCEINLINE const int8 GetPenetrate() const { return _penetrate; }

	FORCEINLINE void SetGold(const int32 i_gold) { _gold = i_gold; }
	FORCEINLINE void SetGem(const int32 i_gem) { _gem = i_gem; }

	FORCEINLINE void SetDMG(const int32 i_dmg) { _dmg = i_dmg; }
	FORCEINLINE void SetAS(const int32 i_as) { _as = i_as; }
	FORCEINLINE void SetShotNumber(const int8 i_shot_number) { _shot_number = i_shot_number; }
	FORCEINLINE void SetPenetrate(const int8 i_penetrate) { _penetrate = i_penetrate; }
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
	//UPROPERTY(EditAnywhere, Category = "General")
		//bool _is_treasure_chest = false;

	UPROPERTY(EditAnywhere, Category = "Stat")
		int16 _move_speed = 500;

	UPROPERTY(EditAnywhere, Category = "Bonus")
		int32 _bonus_gold = 1;
public:
	FORCEINLINE const TSubclassOf<ASA_Monster>& GetClassMonster() const { return _class_monster; }
	FORCEINLINE const FString& GetCode() const { return _code; }
	//FORCEINLINE const bool GetisTreasureChest() const { return _is_treasure_chest; }

	FORCEINLINE const int16 GetMoveSpeed() const { return _move_speed; }
	FORCEINLINE const int32 GetBonusGold() const { return _bonus_gold; }
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
		FVector velocity = FVector::ZeroVector;
	UPROPERTY()
		FRotator rot = FRotator::ZeroRotator;

	UPROPERTY()
		EMonsterHP mob_hp = EMonsterHP::HP_2;
	UPROPERTY()
		int32 hp = 0;
	UPROPERTY()
		int32 hp_max = 0;

	UPROPERTY()
		int16 move_speed = 0;

	UPROPERTY()
		int32 bonus_gold = 0;

	UPROPERTY()
		bool is_treasure_chest = false;
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