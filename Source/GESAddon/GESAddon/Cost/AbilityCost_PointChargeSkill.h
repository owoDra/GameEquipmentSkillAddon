// Copyright (C) 2024 owoDra

#pragma once

#include "Cost/AbilityCost_StatTag.h"

#include "AbilityCost_PointChargeSkill.generated.h"


/**
 * AbilityCost class, of the type that stores percentages and consumes them all at once.
 */
UCLASS(DefaultToInstanced, EditInlineNew, meta = (DisplayName = "Cost Point Charge Skill"))
class GESADDON_API UAbilityCost_PointChargeSkill : public UAbilityCost_StatTag
{
	GENERATED_BODY()
public:
	UAbilityCost_PointChargeSkill(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
