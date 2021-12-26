// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SA_FunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SACLIENT_API USA_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static float GetDistanceByV3(const FVector& v_loc_owner, const FVector& v_loc_target);
	static float GetDistanceByV2(const FVector2D& v_loc_owner, const FVector2D& v_loc_target);
	static FVector GetVelocityByV3(const FVector& v_loc_owner, const FVector& v_loc_target);
	static FVector2D GetVelocityByV2(const FVector2D& v_loc_owner, const FVector2D& v_loc_target);
	static float GetLookRotatorYawByV3(const FVector& v_owner, const FVector& v_target);

	static void GPrintString(int i_key, float f_time, const FString& str_message, const FColor& s_color = FColor::Magenta);
};
