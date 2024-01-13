// Copyright (C) 2024 owoDra

#include "GameplayAbility_PointChargeSkill.h"

#include "GameplayTag/GESATags_Message.h"

#include "GameplayTag/GAETags_Ability.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GameplayAbility_PointChargeSkill)


UGameplayAbility_PointChargeSkill::UGameplayAbility_PointChargeSkill(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	ActivationMethod = EAbilityActivationMethod::OnInputTriggered;
	ActivationPolicy = EAbilityActivationPolicy::Default;

	ActivationMessageTag = TAG_Message_Ability_Activation_Skill;

	CooltimeOverride = 0.0f;
	CooldownMessageTag = FGameplayTag::EmptyTag;
	bUseCooldown = false;

	AbilityTags.AddTag(TAG_Ability_Type_Skill);
}
