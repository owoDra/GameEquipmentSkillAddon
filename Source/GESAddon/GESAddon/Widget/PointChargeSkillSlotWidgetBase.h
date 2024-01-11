// Copyright (C) 2024 owoDra

#pragma once

#include "Widget/EquipmentSlotWidgetBase.h"

// Game Framework Core
#include "GameplayTag/GameplayTagStackMessageTypes.h"
#include "Message/GameplayMessageSubsystem.h"

// Game Ability Extension
#include "Type/AbilityActivationMessageTypes.h"

#include "PointChargeSkillSlotWidgetBase.generated.h"

class UTexture2D;


/**
 * Base widget class that provides the basic functionality for implementing widgets in EquipmentSlot (AbilitySlot)
 */
UCLASS(Abstract, Blueprintable)
class GESADDON_API UPointChargeSkillSlotWidgetBase : public UEquipmentSlotWidgetBase
{
	GENERATED_BODY()
public:
	UPointChargeSkillSlotWidgetBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(AdvancedDisplay, BlueprintReadOnly, EditAnywhere, Category = "Equipment", meta = (Categories = "Message.Ability.Activation.Equipment.Skill"))
	FGameplayTag ActivationMessageTag;

	UPROPERTY(AdvancedDisplay, BlueprintReadOnly, EditAnywhere, Category = "Equipment", meta = (Categories = "Message.Ability.TagStackCountChange"))
	FGameplayTag StatTagStockMessageTag;

	UPROPERTY(AdvancedDisplay, BlueprintReadOnly, EditAnywhere, Category = "Equipment", meta = (Categories = "Stat.Equipment.Skill"))
	FGameplayTag PointStatTag;

	UPROPERTY(AdvancedDisplay, BlueprintReadOnly, EditAnywhere, Category = "Equipment", meta = (Categories = "Stat.Equipment.Skill"))
	FGameplayTag RequiredPointStatTag;

private:
	UPROPERTY(Transient)
	FGameplayMessageListenerHandle ActivationMessageListenerHandle;

	UPROPERTY(Transient)
	FGameplayMessageListenerHandle StatTagStockMessageListenerHandle;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

	void ListenMessageEvents();
	void UnlistenMessageEvents();

private:
	void HandleActivationMessage(FGameplayTag MessageTag, const FAbilityActivationMessage& Message);
	void HandleStatTagStockMessage(FGameplayTag MessageTag, const FGameplayTagStackCountChangeMessage& Message);

protected:
	virtual void SetEquipment(const UEquipmentData* Data, UEquipmentInstance* Instance) override;

	virtual void SetPoint(int32 NewPoint);
	virtual void SetRequiredPoint(int32 NewRequiredPoint);
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Skill")
	void OnSkillActivation();

	UFUNCTION(BlueprintImplementableEvent, Category = "Skill")
	void OnSkillIconChanged(const TSoftObjectPtr<UTexture2D>& Texture);

	UFUNCTION(BlueprintImplementableEvent, Category = "Skill")
	void OnPointChanged(int32 NewPoint);

	UFUNCTION(BlueprintImplementableEvent, Category = "Skill")
	void OnRequiredPointChanged(int32 NewRequiredPoint);

};
