// Copyright (C) 2024 owoDra

#pragma once

#include "Cost/AbilityCost.h"

#include "AbilityCost_PointChargeSkill.generated.h"


/**
 * AbilityCost class, of the type that stores percentages and consumes them all at once.
 */
UCLASS(DefaultToInstanced, EditInlineNew, meta = (DisplayName = "Cost Point Charge Skill"))
class GESADDON_API UAbilityCost_PointChargeSkill : public UAbilityCost
{
	GENERATED_BODY()
public:
	UAbilityCost_PointChargeSkill(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	//
	// Points required to activate skills
	//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Costs")
	FScalableFloat RequiedPoint{ 1.0f };

	//
	// Which tag to spend some of
	//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Costs", meta = (Categories = "Stat.Equipment.Skill"))
	FGameplayTag PointTag;

	//
	// StatTag representing the required cost
	//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Costs", meta = (Categories = "Stat.Equipment.Skill"))
	FGameplayTag RequiedPointTag;

	//
	// Set StatTag at initialization
	//
	UPROPERTY(AdvancedDisplay, BlueprintReadOnly, EditAnywhere, Category = "Costs")
	bool InitStatOnAbilityGive{ true };

	//
	// Whether to own the required points at the time of initialization
	//
	UPROPERTY(AdvancedDisplay, BlueprintReadOnly, EditAnywhere, Category = "Costs")
	bool InitialGiveEnoughPoint{ false };

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

public:
	virtual void OnAvatarSet(
		const UGAEGameplayAbility* Ability
		, const FGameplayAbilityActorInfo* ActorInfo
		, const FGameplayAbilitySpec& Spec) override;

};
