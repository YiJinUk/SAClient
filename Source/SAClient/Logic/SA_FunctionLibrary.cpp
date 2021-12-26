// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/SA_FunctionLibrary.h"

#include "Kismet/KismetMathLibrary.h"

float USA_FunctionLibrary::GetDistanceByV3(const FVector& v_loc_owner, const FVector& v_loc_target)
{
	return (v_loc_owner - v_loc_target).Size();
}
float USA_FunctionLibrary::GetDistanceByV2(const FVector2D& v_loc_owner, const FVector2D& v_loc_target)
{
	return (v_loc_owner - v_loc_target).Size();
}
FVector USA_FunctionLibrary::GetVelocityByV3(const FVector& v_loc_owner, const FVector& v_loc_target)
{
	return (v_loc_target - v_loc_owner).GetSafeNormal();
}
FVector2D USA_FunctionLibrary::GetVelocityByV2(const FVector2D& v_loc_owner, const FVector2D& v_loc_target)
{
	return (v_loc_target - v_loc_owner).GetSafeNormal();
}

float USA_FunctionLibrary::GetLookRotatorYawByV3(const FVector& v_owner, const FVector& v_target)
{
	return UKismetMathLibrary::FindLookAtRotation(v_owner, v_target).Yaw;
}

void USA_FunctionLibrary::GPrintString(int i_key, float f_time, const FString& str_message, const FColor& s_color)
{
	GEngine->AddOnScreenDebugMessage(i_key, f_time, s_color, str_message);
}