#include "CBehaviorComponent.h"
#include "Global.h"

#include "Characters/CPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"

UCBehaviorComponent::UCBehaviorComponent()
{
}

void UCBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UCBehaviorComponent::IsWait()		{ return GetType() == EBehaviorType::Wait; }
bool UCBehaviorComponent::IsApproach()	{ return GetType() == EBehaviorType::Approach; }
bool UCBehaviorComponent::IsAction()	{ return GetType() == EBehaviorType::Action; }
bool UCBehaviorComponent::IsPatrol()	{ return GetType() == EBehaviorType::Patrol; }
bool UCBehaviorComponent::IsHitted()	{ return GetType() == EBehaviorType::Hitted; }
bool UCBehaviorComponent::IsAvoid()		{ return GetType() == EBehaviorType::Avoid; }

void UCBehaviorComponent::SetWait()		{ ChangeType(EBehaviorType::Wait);}
void UCBehaviorComponent::SetApproach()	{ ChangeType(EBehaviorType::Approach);}
void UCBehaviorComponent::SetAction()	{ ChangeType(EBehaviorType::Action);}
void UCBehaviorComponent::SetPatrol()	{ ChangeType(EBehaviorType::Patrol);}
void UCBehaviorComponent::SetHitted()	{ ChangeType(EBehaviorType::Hitted);}
void UCBehaviorComponent::SetAvoid()	{ ChangeType(EBehaviorType::Avoid);}

ACPlayer* UCBehaviorComponent::GetTargetPlayer()
{
	return Cast<ACPlayer>(Blackboard->GetValueAsObject(PlayerKey));
}

FVector UCBehaviorComponent::GetWarpLocation()
{
	return Blackboard->GetValueAsVector(WarpLocationKey);
}

void UCBehaviorComponent::ChangeType(EBehaviorType InType)
{
	EBehaviorType type = GetType();

	Blackboard->SetValueAsEnum(BehaviorKey, (uint8)InType);

	if (OnBehaviorTypeChanged.IsBound())
		OnBehaviorTypeChanged.Broadcast(type, InType);
}

EBehaviorType UCBehaviorComponent::GetType() { return (EBehaviorType)Blackboard->GetValueAsEnum(BehaviorKey); }
