// Copyright (C) 2024 owoDra

#include "AbilityCost_RechargeableSkillStock.h"

// This Plugin
#include "GameplayTag/GESATags_Stat.h"
#include "GESAddonLogs.h"

// Game Framework Core
#include "GameplayTag/GameplayTagStackInterface.h"

// Game Ability Extension
#include "GAEGameplayAbility.h"

// Game Ability: Equipment Addon
#include "EquipmentInstance.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AbilityCost_RechargeableSkillStock)


UAbilityCost_RechargeableSkillStock::UAbilityCost_RechargeableSkillStock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ConsumeTag = TAG_Stat_Equipment_Skill_Stock;
}


bool UAbilityCost_RechargeableSkillStock::CheckCost(const UGAEGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const
{
	// Returns false if EquipmentInstance is not inherited

	auto* EquipmentInstance{ Ability->GetTypedSourceObject<UEquipmentInstance>() };

	if (!EquipmentInstance)
	{
		UE_LOG(LogGESA, Warning, TEXT("UAbilityCost_RechargeableSkillStock::CheckCost: SourceObject in [%s] is not derived from EquipmentInstance"), *GetNameSafe(Ability));
		return false;
	}

	// Check the number of tags

	if (auto* Interface{ Cast<IGameplayTagStackInterface>(EquipmentInstance) })
	{
		return (Interface->GetStatTagStackCount(ConsumeTag) > 0);
	}
	
	return false;
}

void UAbilityCost_RechargeableSkillStock::ApplyCost(const UGAEGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	// Must have authority

	if (!ActorInfo->IsNetAuthority())
	{
		return;
	}

	// If EquipmentInstance is not inherited, skip

	auto* EquipmentInstance{ Ability->GetTypedSourceObject<UEquipmentInstance>() };

	if (!EquipmentInstance)
	{
		UE_LOG(LogGESA, Warning, TEXT("UAbilityCost_RechargeableSkillStock::ApplyCost: SourceObject in [%s] is not derived from EquipmentInstance"), *GetNameSafe(Ability));
		return;
	}

	// Modify the number of tags

	if (auto* Interface{ Cast<IGameplayTagStackInterface>(EquipmentInstance) })
	{
		Interface->RemoveStatTagStack(ConsumeTag, 1);
	}
}


void UAbilityCost_RechargeableSkillStock::OnAvatarSet(const UGAEGameplayAbility* Ability, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	// If InitStatOnAbilityGive is false, skip

	if (!InitStatOnAbilityGive)
	{
		return;
	}

	// Must have authority

	if (!ActorInfo->IsNetAuthority())
	{
		return;
	}

	// If EquipmentInstance is not inherited, Skip

	auto* EquipmentInstance{ Ability->GetTypedSourceObject<UEquipmentInstance>() };

	if (!EquipmentInstance)
	{
		UE_LOG(LogGESA, Warning, TEXT("UAbilityCost_RechargeableSkillStock::OnAvatarSet: SourceObject in [%s] is not derived from EquipmentInstance"), *GetNameSafe(Ability));
		return;
	}

	// Init the number of tags

	if (auto* Interface{ Cast<IGameplayTagStackInterface>(EquipmentInstance) })
	{
		const auto AbilityLevel{ Spec.Level };

		const auto MaxStockReal{ MaxStock.GetValueAtLevel(AbilityLevel) };
		const auto MaxStockValue{ FMath::TruncToInt(MaxStockReal) };

		Interface->SetStatTagStack(ConsumeTag, MaxStockValue);
	}
}


bool UAbilityCost_RechargeableSkillStock::ChargeStock(UEquipmentInstance* Target, float Level)
{
	if (auto* Interface{ Cast<IGameplayTagStackInterface>(Target) })
	{
		const auto MaxStockReal{ MaxStock.GetValueAtLevel(Level) };
		const auto MaxStockValue{ FMath::TruncToInt(MaxStockReal) };

		const auto CurrentStock{ Interface->AddStatTagStack(ConsumeTag, 1) };

		return CurrentStock >= MaxStockValue;
	}

	return true;
}
