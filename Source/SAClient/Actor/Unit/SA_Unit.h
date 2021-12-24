// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/SA_Actor.h"
#include "SA_Unit.generated.h"

/**
 * 
 */
UCLASS()
class SACLIENT_API ASA_Unit : public ASA_Actor
{
	GENERATED_BODY()
	
public:
	ASA_Unit();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* _skeletal_mesh = nullptr;
};
