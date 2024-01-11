// Copyright (C) 2024 owoDra

#include "GameplayAbility_TimeChargeSkill.h"

#include "GameplayTag/GESATags_Ability.h"
#include "GameplayTag/GESATags_Message.h"

#include "GameplayTag/GAETags_Ability.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GameplayAbility_TimeChargeSkill)


UGameplayAbility_TimeChargeSkill::UGameplayAbility_TimeChargeSkill(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	ActivationMethod = EAbilityActivationMethod::OnInputTriggered;
	ActivationPolicy = EAbilityActivationPolicy::CostOverCooldown;

	ActivationMessageTag = TAG_Message_Ability_Activation_Skill;

	CooltimeOverride = 5.0f;
	CooldownTag = TAG_Ability_Cooldown_Skill;
	CooldownMessageTag = TAG_Message_Ability_Cooldown_Skill;
	bShouldListenToCooldownEnd = true;

	AbilityTags.AddTag(TAG_Ability_Type_Skill);
}
