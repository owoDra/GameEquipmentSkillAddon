// Copyright (C) 2024 owoDra

#include "AbilityCost_TimeChargeSkillStock.h"

#include "GESAddonLogs.h"

#include "GAEGameplayAbility.h"

#include "GameplayTag/GameplayTagStackInterface.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AbilityCost_TimeChargeSkillStock)


UAbilityCost_TimeChargeSkillStock::UAbilityCost_TimeChargeSkillStock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAbilityCost_TimeChargeSkillStock::OnCooldownEnd(const UGAEGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	// If EquipmentInstance is not inherited, Skip

	auto* EquipmentInstance{ Ability ? Ability->GetTypedSourceObject<UEquipmentInstance>() : nullptr };

	if (!EquipmentInstance)
	{
		UE_LOG(LogGESA, Warning, TEXT("UAbilityCost_TimeChargeSkillStock::OnCooldownEnd: SourceObject in [%s] is not derived from EquipmentInstance"), *GetNameSafe(Ability));
		return;
	}

	// Modify the number of tags

	if (auto* Interface{ Cast<IGameplayTagStackInterface>(EquipmentInstance) })
	{
		const auto AbilityLevel{ Ability->GetAbilityLevel(Handle, ActorInfo) };

		const auto bIsFull{ ChargeStock(EquipmentInstance, AbilityLevel) };

		if (!bIsFull)
		{
			auto* AbilityNonConst{ const_cast<UGAEGameplayAbility*>(Ability) };

			AbilityNonConst->CommitAbilityCooldown(Handle, ActorInfo, ActivationInfo, false);
		}
	}
}
