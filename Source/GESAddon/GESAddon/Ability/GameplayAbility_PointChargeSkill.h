// Copyright (C) 2024 owoDra

#pragma once

#include "Ability/GameplayAbility_Equipment.h"

#include "GameplayAbility_PointChargeSkill.generated.h"


/**
 * GameplayAbility class with basic implementation for skills
 */
UCLASS(Abstract)
class GESADDON_API UGameplayAbility_PointChargeSkill : public UGameplayAbility_Equipment
{
	GENERATED_BODY()
public:
	UGameplayAbility_PointChargeSkill(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
