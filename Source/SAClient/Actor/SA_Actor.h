// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SA_Actor.generated.h"

UCLASS()
class SACLIENT_API ASA_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASA_Actor();
protected:
	UPROPERTY(EditAnywhere)
		class USceneComponent* _root_scene = nullptr;

public:
	FVector2D GetActorLocation2D();

};
