// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/Monster/SA_Monster.h"
#include "UI/Game/HeadUp/SA_UI_Headup_Monster.h"

#include "Components/WidgetComponent.h"

ASA_Monster::ASA_Monster(FObjectInitializer const& object_initializer)
{
	_ui_headup = object_initializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("_ui_headup"));
	if (_ui_headup)
	{
		_ui_headup->SetupAttachment(GetRootComponent());
		_ui_headup->SetGenerateOverlapEvents(false);
		_ui_headup->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		_ui_headup->CanCharacterStepUpOn = ECB_No;
		_ui_headup->SetWidgetSpace(EWidgetSpace::Screen);
		_ui_headup->SetDrawAtDesiredSize(true);

		static ConstructorHelpers::FClassFinder<UUserWidget> W_HEAD_UP_BP(TEXT("/Game/SAContent/UI/Game/HeadUp/SAWB_UI_HeadUp_Monster"));
		if (W_HEAD_UP_BP.Succeeded())
		{
			if (_ui_headup)
			{
				_ui_headup->SetWidgetClass(W_HEAD_UP_BP.Class);
			}
		}
	}
}

void ASA_Monster::MOBPostInit(const FDataMonster* s_data_monster)
{
	if (!s_data_monster) return;
	_info_monster.code = s_data_monster->GetCode();
	_info_monster.move_speed = s_data_monster->GetMoveSpeed();
	_info_monster.bonus_gold = s_data_monster->GetBonusGold();

	_ui_headup_monster = Cast<USA_UI_Headup_Monster>(_ui_headup->GetUserWidgetObject());
}

void ASA_Monster::MOBInit(const int64 i_id, const EMonsterHP e_monster_hp, const FVector& v_spawn_loc, const FVector& v_velocity, const FRotator& r_rot)
{
	/*Ǯ��*/
	MOBSetPoolActive(true);

	/*���� �ʱ�ȭ*/
	_info_monster.id = i_id;

	/*�̵����� �ʱ�ȭ*/
	_info_monster.velocity = v_velocity;
	_info_monster.rot = r_rot;
	SetActorRotation(_info_monster.rot);
	SetActorLocation(v_spawn_loc);

	/*���� �ʱ�ȭ*/
	_info_monster.mob_hp = e_monster_hp;
	_info_monster.hp_max = GetMonsterHPByEnum(e_monster_hp);
	_info_monster.hp = _info_monster.hp_max;

	/*UI �ʱ�ȭ*/
	_ui_headup_monster->UIInit(_info_monster.hp);
}

void ASA_Monster::MOBMove(const float f_delta_time)
{
	AddActorWorldOffset(_info_monster.velocity * _info_monster.move_speed * f_delta_time);
}

void ASA_Monster::MOBSetPoolActive(const bool b_is_active)
{
	/*
	* ���̷�Ż�Ž�
	*/
	_skeletal_mesh->SetComponentTickEnabled(b_is_active);
	_skeletal_mesh->SetActive(b_is_active);
	_skeletal_mesh->SetVisibility(b_is_active, true);

	/*
	* UI
	* UI������Ʈ�� SetVisibility()�� ȣ���ϸ� ����ƽ���� Draw�Ǵµ�
	* ����ƽ���� UI������Ʈ�� ƽ�� ��Ȱ��ȭ�ϸ� ����� SetVisibility()�Լ��� �۵��� Draw���� �ʽ��ϴ�
	*/
	_ui_headup->SetVisibility(b_is_active);

	if (!b_is_active)
	{
		//Ǯ���� Ȱ��ȭ�ɶ��� ��ġ������ �ٸ������� �մϴ�
		SetActorLocation(FVector(0.f, -1000.f, -500.f));
		GetWorldTimerManager().SetTimerForNextTick(this, &ASA_Monster::MOBTimerUIPool);
	}
	else
	{
		_ui_headup->SetComponentTickEnabled(true);
	}

	MOBSetPoolActiveChild(b_is_active);
}
void ASA_Monster::MOBTimerUIPool()
{
	_ui_headup->SetComponentTickEnabled(false);
}

void ASA_Monster::MOBSetPoolActiveChild(const bool b_is_active)
{
	//override
}

int32 ASA_Monster::MOBChangeHP(const int32 i_change_hp, int32& i_pure_dmg, const bool b_is_add)
{
	if (b_is_add)
	{
		//�ʿ��ұ�?
	}
	else
	{
		_info_monster.hp -= i_change_hp;
		i_pure_dmg = i_change_hp;
		if (_info_monster.hp < 0)
		{
			i_pure_dmg += _info_monster.hp;
			_info_monster.hp = 0;
		}
	}

	_ui_headup_monster->UIUpdateHP(_info_monster.hp);

	return _info_monster.hp;
}

const int32 ASA_Monster::GetMonsterHPByEnum(const EMonsterHP e_monster_hp)
{
	switch (e_monster_hp)
	{
	case EMonsterHP::HP_2:
		return 2;
		break;
	case EMonsterHP::HP_4:
		return 4;
		break;
	case EMonsterHP::HP_8:
		return 8;
		break;
	case EMonsterHP::HP_16:
		return 16;
		break;
	default:
		break;
	}

	return 0;
}

const EMonsterHP ASA_Monster::GetDownMonsterHP() const
{
	switch (_info_monster.mob_hp)
	{
	case EMonsterHP::HP_2:
		return EMonsterHP::HP_NO;
		break;
	case EMonsterHP::HP_4:
		return EMonsterHP::HP_2;
		break;
	case EMonsterHP::HP_8:
		return EMonsterHP::HP_4;
		break;
	case EMonsterHP::HP_16:
		return EMonsterHP::HP_8;
		break;
	default:
		break;
	}

	return EMonsterHP::HP_NO;
}


const FInfoMonster& ASA_Monster::GetInfoMonster() const { return _info_monster; }

