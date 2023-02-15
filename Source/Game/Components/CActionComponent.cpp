#include "CActionComponent.h"
#include "Global.h"

#include "Actions/CActionData.h"
#include "Actions/CActionObject.h"

#include "Actions/CEquipment.h"
#include "Actions/CDoAction.h"
#include "Actions/CAttachment.h"

#include "GameFramework/Character.h"

UCActionComponent::UCActionComponent()
{
}

void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* character =	Cast<ACharacter>(GetOwner());

	for (int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		if (Datas[i] != nullptr)
			Datas[i]->BeginPlay(character, &DataObjects[i]);
	}	
}

void UCActionComponent::SetUnaremdMode()
{
	if (!!DataObjects[(int32)Type] && DataObjects[(int32)Type]->GetEquipment())
		DataObjects[(int32)Type]->GetEquipment()->Unequip();

	DataObjects[(int32)EActionType::Unarmed]->GetEquipment()->Equip();

	ChangeType(EActionType::Unarmed);
}

void UCActionComponent::SetFistMode(){	SetMode(EActionType::Fist);}
void UCActionComponent::SetOneHandMode(){	SetMode(EActionType::OneHand);}
void UCActionComponent::SetTwoHandMode(){	SetMode(EActionType::TwoHand);}
void UCActionComponent::SetWarpMode(){	SetMode(EActionType::Warp);}
void UCActionComponent::SetMagicBallMode(){	SetMode(EActionType::MagicBall);}
void UCActionComponent::SetStormMode(){	SetMode(EActionType::Storm);}

void UCActionComponent::DoAction(){	CheckTrue(IsUnaremdMode());

if (DataObjects[(int32)Type] != nullptr && DataObjects[(int32)Type]->GetDoAction())
	{
		ACDoAction* doAction = DataObjects[(int32)Type]->GetDoAction();

		if(doAction != nullptr)
			doAction->DoAction();
	}
}

void UCActionComponent::DoOnAim()
{
	if (DataObjects[(int32)Type] != nullptr && DataObjects[(int32)Type]->GetDoAction() != nullptr)
	{
		ACDoAction* action = DataObjects[(int32)Type]->GetDoAction();

		action->OnAim();
	}
}

void UCActionComponent::DoOffAim()
{
	if (DataObjects[(int32)Type] != nullptr && DataObjects[(int32)Type]->GetDoAction() != nullptr)
	{
		ACDoAction* action = DataObjects[(int32)Type]->GetDoAction();

		action->OffAim();
	}
}

void UCActionComponent::SetMode(EActionType InNewType)
{
	if (Type == InNewType)
	{
		SetUnaremdMode();
		return;
	}
	else if (IsUnaremdMode() == false)
	{
		if (!!DataObjects[(int32)Type] && DataObjects[(int32)Type]->GetEquipment())
			DataObjects[(int32)Type]->GetEquipment()->Unequip();
	}

	if (!!DataObjects[(int32)InNewType] && DataObjects[(int32)InNewType]->GetEquipment())
		DataObjects[(int32)InNewType]->GetEquipment()->Equip();

	ChangeType(InNewType);
	//Todo. 노티파이
	//Todo. 원핸드 꺼내고 폰컨트롤 켜줘
	//Todo. 구르거나 백대시 버그 수정
}

void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType  prevType = Type;
	Type = InNewType;

	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prevType, InNewType);
}

void UCActionComponent::Dead(){	OffAllCollisions();}
void UCActionComponent::End_Dead()
{
	for (int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		if (DataObjects[i] != nullptr && DataObjects[i]->GetAttachment() != nullptr)
			DataObjects[i]->GetAttachment()->Destroy();

		if (DataObjects[i] != nullptr && DataObjects[i]->GetEquipment() != nullptr)
			DataObjects[i]->GetEquipment()->Destroy();

		if (DataObjects[i] != nullptr && DataObjects[i]->GetDoAction() != nullptr)
			DataObjects[i]->GetDoAction()->Destroy();
	}
}

void UCActionComponent::OffAllCollisions()
{
	for (UCActionObject* data : DataObjects)
	{
		if (data == nullptr)
			continue;

		if (data->GetAttachment() == nullptr)
			continue;

		data->GetAttachment()->OffCollisions();
	}
}

void UCActionComponent::AbortByDamaged()
{
	CheckNull(DataObjects[(int32)Type]);
	CheckTrue(IsUnaremdMode());

	DataObjects[(int32)Type]->GetEquipment()->Begin_Equip();
	DataObjects[(int32)Type]->GetEquipment()->End_Equip();

	DataObjects[(int32)Type]->GetDoAction()->Abort();
}
