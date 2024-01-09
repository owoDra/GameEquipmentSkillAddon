// Copyright (C) 2024 owoDra

#pragma once

#include "Cost/AbilityCost.h"

#include "AbilityCost_RechargeableSkillStock.generated.h"

class UEquipmentInstance;


/**
 * Base AbilityCost class of rechargeable skill stock
 */
UCLASS(Abstract, DefaultToInstanced, EditInlineNew)
class GESADDON_API UAbilityCost_RechargeableSkillStock : public UAbilityCost
{
	GENERATED_BODY()
public:
	UAbilityCost_RechargeableSkillStock(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	//
	// Maximum number of chargeable stocks (keyed on ability level)
	//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Costs")
	FScalableFloat MaxStock{ 1.0f };

	//
	// Which tag to spend some of
	//
	UPROPERTY(AdvancedDisplay, BlueprintReadOnly, EditAnywhere, Category = "Costs", meta = (Categories = "Stat.Equipment.Skill"))
	FGameplayTag ConsumeTag;

	//
	// Which tag to spend some of
	//
	UPROPERTY(AdvancedDisplay, BlueprintReadOnly, EditAnywhere, Category = "Costs")
	bool InitStatOnAbilityGive{ true };

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

protected:
	/**
	 * Charge the number of remaining stock
	 * 
	 * Tips:
	 *	Returns whether max stock is reached as the return value
	 */
	bool ChargeStock(UEquipmentInstance* Target, float Level);

};
