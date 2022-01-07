// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Animation/SA_AM.h"
#include "Logic/SA_GM.h"

void USA_AM::InitSAAM(ASA_GM* sagm)
{
	_sagm = sagm;
}

void USA_AM::DoAttack()
{
	_sagm->ShootPROJ();
}