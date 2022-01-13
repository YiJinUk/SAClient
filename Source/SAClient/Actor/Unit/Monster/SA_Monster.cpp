// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/Monster/SA_Monster.h"
#include "Logic/SA_GI.h"
#include "Actor/Object/SA_SpawnPoint.h"
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

		//static ConstructorHelpers::FClassFinder<UUserWidget> W_HEAD_UP_BP(TEXT("/Game/SAContent/UI/Game/HeadUp/SAWB_UI_HeadUp_Monster"));
		//if (W_HEAD_UP_BP.Succeeded())
		//{
		//	if (_ui_headup)
		//	{
		//		_ui_headup->SetWidgetClass(W_HEAD_UP_BP.Class);
		//	}
		//}
	}
}

void ASA_Monster::MOBPostInit(const FDataMonster* s_data_monster)
{
	_sagi = GetWorld()->GetGameInstance<USA_GI>();
	if (!s_data_monster) return;
	_info_monster.code = s_data_monster->GetCode();
	_info_monster.move_speed = s_data_monster->GetMoveSpeed();
	_info_monster.bonus_gold = s_data_monster->GetBonusGold();

	_ui_headup_monster = Cast<USA_UI_Headup_Monster>(_ui_headup->GetUserWidgetObject());

	MOBPostInitChild(s_data_monster);
}

void ASA_Monster::MOBPostInitChild(const FDataMonster* s_data_monster)
{
	//override
}

void ASA_Monster::MOBInit(const int64 i_id, const EMonsterHP e_monster_hp, ASA_SpawnPoint* obj_spawn_point)
{
	//override

	if (!obj_spawn_point) return;

	/*풀링*/
	MOBSetPoolActive(true);

	/*정보 초기화*/
	_info_monster.id = i_id;

	/*이동관련 초기화*/
	_info_monster.velocity = obj_spawn_point->GetPointVelocity();
	_info_monster.rot = obj_spawn_point->GetPointRotator();
	SetActorRotation(_info_monster.rot);
	SetActorLocation(obj_spawn_point->GetPointSpawnLocation());

	/*스탯 초기화*/
	_info_monster.mob_hp = e_monster_hp;
	_info_monster.hp_max = _sagi->GetMonsterHPByEnum(e_monster_hp);
	_info_monster.hp = _info_monster.hp_max;

	/*UI 초기화*/
	_ui_headup_monster->UIInit(_info_monster.hp);
}

void ASA_Monster::MOBInitClone(const int64 i_id, const EMonsterHP e_monster_hp, const FVector& s_spawn_loc, const FVector& v_velocity, const FRotator& r_rot)
{
	/*풀링*/
	MOBSetPoolActive(true);

	/*정보 초기화*/
	_info_monster.id = i_id;

	/*이동관련 초기화*/
	_info_monster.velocity = v_velocity;
	_info_monster.rot = r_rot;
	SetActorRotation(_info_monster.rot);
	SetActorLocation(s_spawn_loc);

	/*스탯 초기화*/
	_info_monster.mob_hp = e_monster_hp;
	_info_monster.hp_max = _sagi->GetMonsterHPByEnum(e_monster_hp);
	_info_monster.hp = _info_monster.hp_max;

	/*UI 초기화*/
	_ui_headup_monster->UIInit(_info_monster.hp);
}

void ASA_Monster::MOBInitTreasureChest(const int64 i_id, const int32 i_hp, const int32 i_drop_gem, const FVector& s_spawn_loc)
{
	/*풀링*/
	MOBSetPoolActive(true);

	/*정보 초기화*/
	_info_monster.id = i_id;

	/*이동관련 정보는 PostInit에서 설정했기 때문에 여기서 설정하지 않습니다*/
	SetActorLocation(s_spawn_loc);

	/*스탯 초기화*/
	_info_monster.hp_max = i_hp;
	_info_monster.hp = i_hp;
	_info_monster.bonus_gold = i_drop_gem;

	/*UI 초기화*/
	_ui_headup_monster->UIInit(_info_monster.hp);
}


void ASA_Monster::MOBMove(const float f_delta_time)
{
	AddActorWorldOffset(_info_monster.velocity * _info_monster.move_speed * f_delta_time);
}

void ASA_Monster::MOBSetPoolActive(const bool b_is_active)
{
	/*
	* 스켈레탈매쉬
	*/
	_skeletal_mesh->SetComponentTickEnabled(b_is_active);
	_skeletal_mesh->SetActive(b_is_active);
	_skeletal_mesh->SetVisibility(b_is_active, true);

	/*
	* UI
	* UI컴포넌트의 SetVisibility()를 호출하면 다음틱에서 Draw되는데
	* 같은틱에서 UI컴포넌트의 틱을 비활성화하면 제대로 SetVisibility()함수의 작동이 Draw되지 않습니다
	*/
	_ui_headup->SetVisibility(b_is_active);

	if (!b_is_active)
	{
		//풀에서 활성화될때의 위치변경은 다른곳에서 합니다
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
		//필요할까?
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

