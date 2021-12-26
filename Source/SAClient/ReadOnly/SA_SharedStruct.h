// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Runtime/CoreUObject/Public/Templates/SubclassOf.h"
#include "UObject/NoExportTypes.h"
#include "SA_SharedStruct.generated.h"

class ASA_Monster;
class ASA_Projectile;

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
	STAND_BY, // 웨이브가 끝나고 쉬는시간
	GAMEOVER, // 게임오버
};

UENUM()
enum class EUIMainStatus : uint8
{
	TITLE,
	GAME,
};

USTRUCT(BlueprintType)
struct FDataGame : public FTableRowBase
{
	GENERATED_BODY()
protected:
	//목표지점 반경입니다
	UPROPERTY(EditAnywhere, Category = "Wave")
		int16 _dest_radius = 100;

	UPROPERTY(EditAnywhere, Category = "Player")
		int16 _player_hp = 100;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		int16 _proj_speed = 1000;
	UPROPERTY(EditAnywhere, Category = "Projectile")
		int16 _proj_range = 100;
	UPROPERTY(EditAnywhere, Category = "Projectile")
		int8 _proj_z_fixed = 50;
public:
	FORCEINLINE const int16 GetDestRadius() const { return _dest_radius; }
	FORCEINLINE const int16 GetPlayetHP() const { return _player_hp; }

	FORCEINLINE const int16 GetPROJSpeed() const { return _proj_speed; }
	FORCEINLINE const int16 GetPROJRange() const { return _proj_range; }
	FORCEINLINE const int8 GetPROJZFixed() const { return _proj_z_fixed; }
};

USTRUCT()
struct FInfoPlayer
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

	UPROPERTY(EditAnywhere, Category = "Stat")
		int32 _hp = 100;
	UPROPERTY(EditAnywhere, Category = "Stat")
		int16 _move_speed = 500;
public:
	FORCEINLINE const TSubclassOf<ASA_Monster>& GetClassMonster() const { return _class_monster; }
	FORCEINLINE const FString& GetCode() const { return _code; }
	FORCEINLINE const int32& GetHP() const { return _hp; }
	FORCEINLINE const int16& GetMoveSpeed() const { return _move_speed; }
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
		int32 hp = 0;
	UPROPERTY()
		int32 hp_max = 0;

	UPROPERTY()
		int16 move_speed = 0;
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
};