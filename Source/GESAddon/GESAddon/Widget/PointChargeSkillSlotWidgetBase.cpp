// Copyright (C) 2024 owoDra

#include "PointChargeSkillSlotWidgetBase.h"

#include "GameplayTag/GESATags_Message.h"
#include "GameplayTag/GESATags_Stat.h"

// Game Framework Core
#include "GameplayTag/GameplayTagStackInterface.h"

// Game Ability: Equipment Addon
#include "EquipmentInstance.h"
#include "EquipmentData.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(PointChargeSkillSlotWidgetBase)


UPointChargeSkillSlotWidgetBase::UPointChargeSkillSlotWidgetBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ActivationMessageTag = TAG_Message_Ability_Activation_Skill;
	StatTagStockMessageTag = TAG_Message_TagStackCountChange;
	PointStatTag = TAG_Stat_Equipment_Skill_Point;
}


void UPointChargeSkillSlotWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ListenMessageEvents();
}

void UPointChargeSkillSlotWidgetBase::NativeDestruct()
{
	Super::NativeDestruct();

	UnlistenMessageEvents();
}


void UPointChargeSkillSlotWidgetBase::ListenMessageEvents()
{
	if (const auto* World{ GetWorld() })
	{
		auto& Subsystem{ UGameplayMessageSubsystem::Get(World) };

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

void UPointChargeSkillSlotWidgetBase::UnlistenMessageEvents()
{
	if (const auto* World{ GetWorld() })
	{
		auto& Subsystem{ UGameplayMessageSubsystem::Get(World) };

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


void UPointChargeSkillSlotWidgetBase::HandleActivationMessage(FGameplayTag MessageTag, const FAbilityActivationMessage& Message)
{
	if (EquipmentInstance.IsValid())
	{
		if ((Message.SourceObject == EquipmentInstance) && (Message.AvatarActor == GetOwningPlayerPawn()))
		{
			OnSkillActivation();
		}
	}
}

void UPointChargeSkillSlotWidgetBase::HandleStatTagStockMessage(FGameplayTag MessageTag, const FGameplayTagStackCountChangeMessage& Message)
{
	if (EquipmentInstance.IsValid())
	{
		if (Message.OwningObject == GetCostTarget<UObject>())
		{
			if (Message.Tag == PointStatTag)
			{
				SetPoint(Message.Count);
				SetRequiredPoint(Message.MaxCount);
			}
		}
	}
}


void UPointChargeSkillSlotWidgetBase::SetEquipment(const UEquipmentData* Data, UEquipmentInstance* Instance)
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

	if (auto* Interface{ GetCostTarget<IGameplayTagStackInterface>() })
	{
		SetRequiredPoint(Interface->GetMaxStatTagStackCount(PointStatTag));
		SetPoint(Interface->GetStatTagStackCount(PointStatTag));
	}
	else
	{
		SetPoint(0);
		SetRequiredPoint(100);
	}
}

void UPointChargeSkillSlotWidgetBase::SetPoint(int32 NewPoint)
{
	OnPointChanged(NewPoint);
}

void UPointChargeSkillSlotWidgetBase::SetRequiredPoint(int32 NewRequiredPoint)
{
	OnRequiredPointChanged(NewRequiredPoint);
}
