// Copyright (C) 2024 owoDra

#include "AbilityCost_PercentChangedSkill.h"

// This Plugin
#include "GameplayTag/GESATags_Stat.h"
#include "GESAddonLogs.h"

// Game Framework Core
#include "GameplayTag/GameplayTagStackInterface.h"

// Game Ability Extension
#include "GAEGameplayAbility.h"

// Game Ability: Equipment Addon
#include "EquipmentInstance.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AbilityCost_PercentChangedSkill)


UAbilityCost_PercentChangedSkill::UAbilityCost_PercentChangedSkill(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ConsumeTag = TAG_Stat_Equipment_Skill_Percent;
}


bool UAbilityCost_PercentChangedSkill::CheckCost(const UGAEGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const
{
	// Returns false if EquipmentInstance is not inherited

	auto* EquipmentInstance{ Ability->GetTypedSourceObject<UEquipmentInstance>() };

	if (!EquipmentInstance)
	{
		UE_LOG(LogGESA, Warning, TEXT("UAbilityCost_PercentChangedSkill::CheckCost: SourceObject in [%s] is not derived from EquipmentInstance"), *GetNameSafe(Ability));
		return false;
	}

	// Check the number of tags

	if (auto* Interface{ Cast<IGameplayTagStackInterface>(EquipmentInstance) })
	{
		return (Interface->GetStatTagStackCount(ConsumeTag) >= 100);
	}
	
	return false;
}

void UAbilityCost_PercentChangedSkill::ApplyCost(const UGAEGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
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
		UE_LOG(LogGESA, Warning, TEXT("UAbilityCost_PercentChangedSkill::ApplyCost: SourceObject in [%s] is not derived from EquipmentInstance"), *GetNameSafe(Ability));
		return;
	}

	// Modify the number of tags

	if (auto* Interface{ Cast<IGameplayTagStackInterface>(EquipmentInstance) })
	{
		Interface->SetStatTagStack(ConsumeTag, 0);
	}
}
