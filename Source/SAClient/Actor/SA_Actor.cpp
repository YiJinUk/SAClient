// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SA_Actor.h"

ASA_Actor::ASA_Actor()
{
	PrimaryActorTick.bCanEverTick = false;

	_root_scene = CreateDefaultSubobject<USceneComponent>("_root_scene");
	if (_root_scene)
	{
		RootComponent = _root_scene;
	}
}

FVector2D ASA_Actor::GetActorLocation2D()
{
	return FVector2D(GetActorLocation().X, GetActorLocation().Y);
}