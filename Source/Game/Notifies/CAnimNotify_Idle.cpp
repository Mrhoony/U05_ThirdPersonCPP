#include "CAnimNotify_Idle.h"
#include "Global.h"
#include "Components/CStateComponent.h"

FString UCAnimNotify_Idle::GetNotifyName_Implementation() const
{
	return "SetIdle";
}

void UCAnimNotify_Idle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(MeshComp->GetOwner());
	CheckNull(state);

	state->SetIdleMode();
}