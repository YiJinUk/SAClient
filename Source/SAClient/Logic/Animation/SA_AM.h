// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SA_AM.generated.h"

class ASA_GM;

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_AM : public UAnimInstance
{
	GENERATED_BODY()

public:
	void InitSAAM(ASA_GM* sagm);
	UFUNCTION(BlueprintCallable)
		void DoAttack();
private:
	UPROPERTY()
		ASA_GM* _sagm = nullptr;
};
