// Copyright (C) 2024 owoDra

#include "AbilityCost_PointChargeSkill.h"

// This Plugin
#include "GameplayTag/GESATags_Stat.h"
#include "GESAddonLogs.h"

// Game Framework Core
#include "GameplayTag/GameplayTagStackInterface.h"

// Game Ability Extension
#include "GAEGameplayAbility.h"

// Game Ability: Equipment Addon
#include "EquipmentInstance.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AbilityCost_PointChargeSkill)


UAbilityCost_PointChargeSkill::UAbilityCost_PointChargeSkill(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PointTag = TAG_Stat_Equipment_Skill_Point;
	RequiedPointTag = TAG_Stat_Equipment_Skill_RequiredPoint;
}


bool UAbilityCost_PointChargeSkill::CheckCost(const UGAEGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const
{
	// Returns false if EquipmentInstance is not inherited

	auto* EquipmentInstance{ Ability->GetTypedSourceObject<UEquipmentInstance>() };

	if (!EquipmentInstance)
	{
		UE_LOG(LogGESA, Warning, TEXT("UAbilityCost_PointChargeSkill::CheckCost: SourceObject in [%s] is not derived from EquipmentInstance"), *GetNameSafe(Ability));
		return false;
	}

	// Check the number of tags

	if (auto* Interface{ Cast<IGameplayTagStackInterface>(EquipmentInstance) })
	{
		const auto AbilityLevel{ Ability->GetAbilityLevel() };

		const auto RequiedPointReal{ RequiedPoint.GetValueAtLevel(AbilityLevel) };
		const auto RequiedPointValue{ FMath::TruncToInt(RequiedPointReal) };

		return (Interface->GetStatTagStackCount(PointTag) >= RequiedPointValue);
	}
	
	return false;
}

void UAbilityCost_PointChargeSkill::ApplyCost(const UGAEGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
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
		UE_LOG(LogGESA, Warning, TEXT("UAbilityCost_PointChargeSkill::ApplyCost: SourceObject in [%s] is not derived from EquipmentInstance"), *GetNameSafe(Ability));
		return;
	}

	// Modify the number of tags

	if (auto* Interface{ Cast<IGameplayTagStackInterface>(EquipmentInstance) })
	{
		Interface->SetStatTagStack(PointTag, 0);
	}
}

void UAbilityCost_PointChargeSkill::OnAvatarSet(const UGAEGameplayAbility* Ability, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
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
		UE_LOG(LogGESA, Warning, TEXT("UAbilityCost_PointChargeSkill::OnAvatarSet: SourceObject in [%s] is not derived from EquipmentInstance"), *GetNameSafe(Ability));
		return;
	}

	// Init the number of tags

	if (auto * Interface{ Cast<IGameplayTagStackInterface>(EquipmentInstance) })
	{
		const auto AbilityLevel{ Spec.Level };

		const auto RequiedPointReal{ RequiedPoint.GetValueAtLevel(AbilityLevel) };
		const auto RequiedPointValue{ FMath::TruncToInt(RequiedPointReal) };

		Interface->SetStatTagStack(PointTag, InitialGiveEnoughPoint ? RequiedPointValue : 0);
		Interface->SetStatTagStack(RequiedPointTag, RequiedPointValue);
	}
}
