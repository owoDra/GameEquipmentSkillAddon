// Copyright (C) 2024 owoDra

#pragma once

#include "GAEGameplayAbility.h"

#include "GameplayAbility_PointChargeSkill.generated.h"


/**
 * GameplayAbility class with basic implementation for skills
 */
UCLASS(Abstract)
class GESADDON_API UGameplayAbility_PointChargeSkill : public UGAEGameplayAbility
{
	GENERATED_BODY()
public:
	UGameplayAbility_PointChargeSkill(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
