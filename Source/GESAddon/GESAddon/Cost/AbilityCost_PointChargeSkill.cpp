// Copyright (C) 2024 owoDra

#include "AbilityCost_PointChargeSkill.h"

#include "GameplayTag/GESATags_Stat.h"
#include "GESAddonLogs.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AbilityCost_PointChargeSkill)


UAbilityCost_PointChargeSkill::UAbilityCost_PointChargeSkill(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	auto& Cost{ StatTagCosts.AddDefaulted_GetRef() };
	Cost.StatTag = TAG_Stat_Equipment_Skill_Point;
	Cost.Target = EStatTagCostTarget::PlayerState;
	Cost.Cost = 100.0f;
	Cost.MaxValue = 100.0f;
	Cost.DefaultValue = 0.0f;
	Cost.bShouldInitStatTag = true;
}
