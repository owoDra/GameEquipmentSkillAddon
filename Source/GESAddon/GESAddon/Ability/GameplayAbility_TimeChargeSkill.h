// Copyright (C) 2024 owoDra

#pragma once

#include "Ability/GameplayAbility_Equipment.h"

#include "GameplayAbility_TimeChargeSkill.generated.h"


/**
 * GameplayAbility class with basic implementation for skills
 */
UCLASS(Abstract)
class GESADDON_API UGameplayAbility_TimeChargeSkill : public UGameplayAbility_Equipment
{
	GENERATED_BODY()
public:
	UGameplayAbility_TimeChargeSkill(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
