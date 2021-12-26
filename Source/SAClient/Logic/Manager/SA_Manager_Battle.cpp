// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/SA_Manager_Battle.h"
#include "Actor/Unit/Monster/SA_Monster.h"

void ASA_Manager_Battle::BattleCalcStart(ASA_Projectile* proj, ASA_Monster* monster, const int32 i_dmg)
{
	if (!proj || !monster) return;

	/*
	* ������ ü���� ����ϴ�
	* UI�� ���� ������Ʈ �մϴ�
	*/
	int32 i_remain_hp = monster->MOBChangeHP(i_dmg);

	/*���Ͱ� �׾��ٸ� Ǯ��*/
	if (i_remain_hp)
	{

	}
}