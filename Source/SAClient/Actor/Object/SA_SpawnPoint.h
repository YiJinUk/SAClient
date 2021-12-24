// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Object/SA_Object.h"
#include "SA_SpawnPoint.generated.h"

/**
 * 
 */
UCLASS()
class SACLIENT_API ASA_SpawnPoint : public ASA_Object
{
	GENERATED_BODY()

public:
	void SpawnPointInit(const FVector& v_dest);

	FORCEINLINE const FRotator& GetPointRotator() const;
	FORCEINLINE const FVector& GetPointVelocity() const;
	FORCEINLINE const FVector& GetPointSpawnLocation() const;
private:
	UPROPERTY()
		FRotator _rot = FRotator::ZeroRotator;
	UPROPERTY()
		FVector _velocity = FVector::ZeroVector;
	UPROPERTY()
		FVector _spawn_loc = FVector::ZeroVector;
};
