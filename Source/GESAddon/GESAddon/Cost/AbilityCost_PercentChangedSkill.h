// Copyright (C) 2024 owoDra

#pragma once

#include "Cost/AbilityCost.h"

#include "AbilityCost_PercentChangedSkill.generated.h"


/**
 * AbilityCost class, of the type that stores percentages and consumes them all at once.
 */
UCLASS(DefaultToInstanced, EditInlineNew, meta = (DisplayName = "Cost Percent Changed Skill"))
class GESADDON_API UAbilityCost_PercentChangedSkill : public UAbilityCost
{
	GENERATED_BODY()
public:
	UAbilityCost_PercentChangedSkill(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	//
	// Which tag to spend some of
	//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Costs", meta = (Categories = "Stat.Equipment.Skill"))
	FGameplayTag ConsumeTag;

public:
	virtual bool CheckCost(
		const UGAEGameplayAbility* Ability
		, const FGameplayAbilitySpecHandle Handle
		, const FGameplayAbilityActorInfo* ActorInfo
		, FGameplayTagContainer* OptionalRelevantTags) const override;

	virtual void ApplyCost(
		const UGAEGameplayAbility* Ability
		, const FGameplayAbilitySpecHandle Handle
		, const FGameplayAbilityActorInfo* ActorInfo
		, const FGameplayAbilityActivationInfo ActivationInfo) override;

};
