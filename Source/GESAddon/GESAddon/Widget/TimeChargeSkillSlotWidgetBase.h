// Copyright (C) 2024 owoDra

#pragma once

#include "Widget/EquipmentSlotWidgetBase.h"

// Game Framework Core
#include "GameplayTag/GameplayTagStackMessageTypes.h"
#include "Message/GameplayMessageSubsystem.h"

// Game Ability Extension
#include "Type/AbilityActivationMessageTypes.h"
#include "Type/AbilityCooldownMessageTypes.h"

#include "TimeChargeSkillSlotWidgetBase.generated.h"

class UTexture2D;


/**
 * Base widget class that provides the basic functionality for implementing widgets in EquipmentSlot (AbilitySlot)
 */
UCLASS(Abstract, Blueprintable)
class GESADDON_API UTimeChargeSkillSlotWidgetBase : public UEquipmentSlotWidgetBase
{
	GENERATED_BODY()
public:
	UTimeChargeSkillSlotWidgetBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(AdvancedDisplay, BlueprintReadOnly, EditAnywhere, Category = "Equipment", meta = (Categories = "Message.Ability.Cooldown.Equipment.Skill"))
	FGameplayTag CooldownMessageTag;

	UPROPERTY(AdvancedDisplay, BlueprintReadOnly, EditAnywhere, Category = "Equipment", meta = (Categories = "Message.Ability.Activation.Equipment.Skill"))
	FGameplayTag ActivationMessageTag;

	UPROPERTY(AdvancedDisplay, BlueprintReadOnly, EditAnywhere, Category = "Equipment", meta = (Categories = "Message.Ability.TagStackCountChange"))
	FGameplayTag StatTagStockMessageTag;

	UPROPERTY(AdvancedDisplay, BlueprintReadOnly, EditAnywhere, Category = "Equipment", meta = (Categories = "Stat.Equipment.Skill"))
	FGameplayTag StockStatTag;

private:
	UPROPERTY(Transient)
	FGameplayMessageListenerHandle CooldownMessageListenerHandle;

	UPROPERTY(Transient)
	FGameplayMessageListenerHandle ActivationMessageListenerHandle;

	UPROPERTY(Transient)
	FGameplayMessageListenerHandle StatTagStockMessageListenerHandle;

protected:
	UPROPERTY(BlueprintReadOnly, Transient, Category = "Cooldown")
	float CurrentCooltime{ 0.0f };

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

	void ListenMessageEvents();
	void UnlistenMessageEvents();

private:
	void HandleCooldownMessage(FGameplayTag MessageTag, const FAbilityCooldownMessage& Message);
	void HandleActivationMessage(FGameplayTag MessageTag, const FAbilityActivationMessage& Message);
	void HandleStatTagStockMessage(FGameplayTag MessageTag, const FGameplayTagStackCountChangeMessage& Message);

protected:
	virtual void SetEquipment(const UEquipmentData* Data, UEquipmentInstance* Instance) override;

	virtual void SetCooltime(float InDuration);
	virtual void SetMaxStock(int32 NewMaxStock);
	virtual void SetStock(int32 NewStock);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Skill")
	void OnSkillActivation();

	UFUNCTION(BlueprintImplementableEvent, Category = "Skill")
	void OnCooldownStart(float TimelinePlayRate);

	UFUNCTION(BlueprintImplementableEvent, Category = "Skill")
	void OnCooldownEnd();

	UFUNCTION(BlueprintImplementableEvent, Category = "Skill")
	void OnSkillIconChanged(const TSoftObjectPtr<UTexture2D>& Texture);

	UFUNCTION(BlueprintImplementableEvent, Category = "Skill")
	void OnMaxStockChanged(int32 NewMaxStock);

	UFUNCTION(BlueprintImplementableEvent, Category = "Skill")
	void OnStockChanged(int32 NewStock);

};
