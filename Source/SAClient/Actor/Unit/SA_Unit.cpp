// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/SA_Unit.h"

#include "Components/SkeletalMeshComponent.h"

ASA_Unit::ASA_Unit()
{
	_skeletal_mesh = CreateDefaultSubobject<USkeletalMeshComponent>("_skeletal_mesh");
	if (_skeletal_mesh)
	{
		_skeletal_mesh->SetupAttachment(GetRootComponent());
		_skeletal_mesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

		_skeletal_mesh->SetSimulatePhysics(false);
		_skeletal_mesh->SetGenerateOverlapEvents(false);
		_skeletal_mesh->SetCanEverAffectNavigation(false);
		_skeletal_mesh->bSkipKinematicUpdateWhenInterpolating = true;
		_skeletal_mesh->bSkipBoundsUpdateWhenInterpolating = true;
		_skeletal_mesh->bComponentUseFixedSkelBounds = true;
		_skeletal_mesh->bEnableUpdateRateOptimizations = true;
	}
}