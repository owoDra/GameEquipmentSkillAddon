// Copyright (C) 2024 owoDra

#pragma once

#include "GAEGameplayAbility.h"

#include "GameplayAbility_TimeChargeSkill.generated.h"


/**
 * GameplayAbility class with basic implementation for skills
 */
UCLASS(Abstract)
class GESADDON_API UGameplayAbility_TimeChargeSkill : public UGAEGameplayAbility
{
	GENERATED_BODY()
public:
	UGameplayAbility_TimeChargeSkill(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
