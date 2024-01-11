// Copyright (C) 2024 owoDra

#include "TimeChargeSkillSlotWidgetBase.h"

#include "GameplayTag/GESATags_Message.h"
#include "GameplayTag/GESATags_Stat.h"

// Game Ability: Equipment Addon
#include "EquipmentInstance.h"
#include "EquipmentData.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(TimeChargeSkillSlotWidgetBase)


UTimeChargeSkillSlotWidgetBase::UTimeChargeSkillSlotWidgetBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CooldownMessageTag = TAG_Message_Ability_Cooldown_Skill;
	ActivationMessageTag = TAG_Message_Ability_Activation_Skill;
	StatTagStockMessageTag = TAG_Message_TagStackCountChange;
	StockStatTag = TAG_Stat_Equipment_Skill_Stock;
	MaxStockStatTag = TAG_Stat_Equipment_Skill_MaxStock;
}


void UTimeChargeSkillSlotWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ListenMessageEvents();
}

void UTimeChargeSkillSlotWidgetBase::NativeDestruct()
{
	Super::NativeDestruct();

	UnlistenMessageEvents();
}


void UTimeChargeSkillSlotWidgetBase::ListenMessageEvents()
{
	if (const auto* World{ GetWorld() })
	{
		auto& Subsystem{ UGameplayMessageSubsystem::Get(World) };

		if (CooldownMessageTag.IsValid())
		{
			CooldownMessageListenerHandle = Subsystem.RegisterListener<FAbilityCooldownMessage>(CooldownMessageTag, this, &ThisClass::HandleCooldownMessage);
		}

		if (ActivationMessageTag.IsValid())
		{
			ActivationMessageListenerHandle = Subsystem.RegisterListener<FAbilityActivationMessage>(ActivationMessageTag, this, &ThisClass::HandleActivationMessage);
		}

		if (StatTagStockMessageTag.IsValid())
		{
			StatTagStockMessageListenerHandle = Subsystem.RegisterListener<FGameplayTagStackCountChangeMessage>(StatTagStockMessageTag, this, &ThisClass::HandleStatTagStockMessage);
		}
	}
}

void UTimeChargeSkillSlotWidgetBase::UnlistenMessageEvents()
{
	if (const auto* World{ GetWorld() })
	{
		auto& Subsystem{ UGameplayMessageSubsystem::Get(World) };

		if (CooldownMessageListenerHandle.IsValid())
		{
			Subsystem.UnregisterListener(CooldownMessageListenerHandle);
		}

		if (ActivationMessageListenerHandle.IsValid())
		{
			Subsystem.UnregisterListener(ActivationMessageListenerHandle);
		}

		if (StatTagStockMessageListenerHandle.IsValid())
		{
			Subsystem.UnregisterListener(StatTagStockMessageListenerHandle);
		}
	}
}


void UTimeChargeSkillSlotWidgetBase::HandleCooldownMessage(FGameplayTag MessageTag, const FAbilityCooldownMessage& Message)
{
	if (EquipmentInstance.IsValid())
	{
		if ((Message.SourceObject == EquipmentInstance) && (Message.AvatarActor == GetOwningPlayerPawn()))
		{
			SetCooltime(Message.Duration);
		}
	}
}

void UTimeChargeSkillSlotWidgetBase::HandleActivationMessage(FGameplayTag MessageTag, const FAbilityActivationMessage& Message)
{
	if (EquipmentInstance.IsValid())
	{
		if ((Message.SourceObject == EquipmentInstance) && (Message.AvatarActor == GetOwningPlayerPawn()))
		{
			OnSkillActivation();
		}
	}
}

void UTimeChargeSkillSlotWidgetBase::HandleStatTagStockMessage(FGameplayTag MessageTag, const FGameplayTagStackCountChangeMessage& Message)
{
	if (EquipmentInstance.IsValid())
	{
		if (Message.OwningObject == EquipmentInstance)
		{
			if (Message.Tag == StockStatTag)
			{
				SetStock(Message.Count);
			}
			else if (Message.Tag == MaxStockStatTag)
			{
				SetMaxStock(Message.Count);
			}
		}
	}
}


void UTimeChargeSkillSlotWidgetBase::SetEquipment(const UEquipmentData* Data, UEquipmentInstance* Instance)
{
	Super::SetEquipment(Data, Instance);

	if (Data)
	{
		OnSkillIconChanged(Data->Image);
	}
	else
	{
		OnSkillIconChanged(nullptr);
	}

	if (Instance)
	{
		SetCooltime(0.0f);
		SetMaxStock(Instance->GetStatTagStackCount(MaxStockStatTag));
		SetStock(Instance->GetStatTagStackCount(StockStatTag));
	}
	else
	{
		SetCooltime(0.0f);
		SetMaxStock(1);
		SetStock(1);
	}
}

void UTimeChargeSkillSlotWidgetBase::SetCooltime(float InDuration)
{
	CurrentCooltime = InDuration;

	const auto bNewIsCoolingdown{ CurrentCooltime > 0.0f };

	if (bNewIsCoolingdown)
	{
		const auto PlayRate{ 1.0f / CurrentCooltime };

		OnCooldownStart(PlayRate);
	}
	else
	{
		OnCooldownEnd();
	}
}

void UTimeChargeSkillSlotWidgetBase::SetMaxStock(int32 NewMaxStock)
{
	OnMaxStockChanged(NewMaxStock);
}

void UTimeChargeSkillSlotWidgetBase::SetStock(int32 NewStock)
{
	OnStockChanged(NewStock);
}
