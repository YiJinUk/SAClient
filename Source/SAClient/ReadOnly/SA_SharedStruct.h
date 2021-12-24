// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Runtime/CoreUObject/Public/Templates/SubclassOf.h"
#include "UObject/NoExportTypes.h"
#include "SA_SharedStruct.generated.h"

class ASA_Monster;

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
	MAIN, // 게임시작전 UI화면 입니다
	PLAY, // 웨이브중
	STAND_BY // 웨이브가 끝나고 쉬는시간
};

USTRUCT(BlueprintType)
struct FDataGame : public FTableRowBase
{
	GENERATED_BODY()
protected:
	//목표지점 반경입니다
	UPROPERTY(EditAnywhere, Category = "Wave")
		int32 _dest_radius = 100;

	UPROPERTY(EditAnywhere, Category = "Player")
		int32 _player_hp = 100;
public:
	FORCEINLINE const int32 GetDestRadius() const { return _dest_radius; }
	FORCEINLINE const int32 GetPlayetHP() const { return _player_hp; }
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

public:
	FORCEINLINE const FString& GetCode() const { return _code; }
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
};

USTRUCT()
struct FInfoPlayer
{
	GENERATED_BODY()

public:
	UPROPERTY()
		int32 hp = 0;
};