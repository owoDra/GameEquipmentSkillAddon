// Copyright (C) 2024 owoDra

#pragma once

#include "Cost/AbilityCost_StatTag.h"

#include "AbilityCost_TimeChargeSkillStock.generated.h"


/**
 * AbilityCost class to recharge skill stock with cool time
 */
UCLASS(DefaultToInstanced, EditInlineNew, meta = (DisplayName = "Cost Time Charge Skill Stock"))
class UAbilityCost_TimeChargeSkillStock : public UAbilityCost_StatTag
{
	GENERATED_BODY()
public:
	UAbilityCost_TimeChargeSkillStock(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	//
	// Whether the StatTag refers to the OwningActor or the AvatarActor
	//
	UPROPERTY(AdvancedDisplay, BlueprintReadOnly, EditAnywhere, Category = "Costs")
	FScalableFloat NumToCharge{ 1.0f };

public:
	virtual void OnCooldownEnd(
		const UGAEGameplayAbility* Ability
		, const FGameplayAbilitySpecHandle Handle
		, const FGameplayAbilityActorInfo* ActorInfo
		, const FGameplayAbilityActivationInfo ActivationInfo);

};
