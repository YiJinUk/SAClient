// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/SA_SharedStruct.h"
#include "Engine/GameInstance.h"
#include "SA_GI.generated.h"

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_GI : public UGameInstance
{
	GENERATED_BODY()

#pragma region Init
protected:
	USA_GI();
public:
	void GIInit();
#pragma endregion

#pragma region DataFind,Get
public:
	FDataMonster* FindDataMonsterByCode(const FString& str_code_monster);
	FDataProjectile* FindDataPROJByCode(const FString& str_code_proj);

	FORCEINLINE FDataGame* GetDataGame();
private:
	UPROPERTY()
		UDataTable* _dt_game = nullptr;
	UPROPERTY()
		UDataTable* _dt_monster = nullptr;
	UPROPERTY()
		UDataTable* _dt_projectile = nullptr;

	FDataGame* _data_game = nullptr;
#pragma endregion
};
