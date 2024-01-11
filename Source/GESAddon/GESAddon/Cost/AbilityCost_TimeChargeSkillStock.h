// Copyright (C) 2024 owoDra

#pragma once

#include "Cost/AbilityCost_RechargeableSkillStock.h"

#include "AbilityCost_TimeChargeSkillStock.generated.h"


/**
 * AbilityCost class to recharge skill stock with cool time
 */
UCLASS(DefaultToInstanced, EditInlineNew, meta = (DisplayName = "Cost Time Recharge Skill Stock"))
class UAbilityCost_TimeChargeSkillStock : public UAbilityCost_RechargeableSkillStock
{
	GENERATED_BODY()
public:
	UAbilityCost_TimeChargeSkillStock(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void OnCooldownEnd(
		const UGAEGameplayAbility* Ability
		, const FGameplayAbilitySpecHandle Handle
		, const FGameplayAbilityActorInfo* ActorInfo
		, const FGameplayAbilityActivationInfo ActivationInfo);

};
