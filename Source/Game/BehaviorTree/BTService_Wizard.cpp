#include "BTService_Wizard.h"
#include "Global.h"

#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CPlayer.h"

UBTService_Wizard::UBTService_Wizard()
{
	NodeName = "Wizard";
}

void UBTService_Wizard::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);

	ACEnemy_AI* aiPawn = Cast<ACEnemy_AI>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);

	CheckTrue(state->IsDeadMode());

	if (state->IsHittedMode())
	{
		behavior->SetHitted();
		return;
	}

	ACPlayer* target = behavior->GetTargetPlayer();
	if (target == nullptr)
	{
		behavior->SetWait();
		controller->ClearFocus(EAIFocusPriority::Gameplay);
		return;
	}
	else
	{
		UCStateComponent* targetState = CHelpers::GetComponent<UCStateComponent>(target);
		if (targetState->IsDeadMode())
		{
			behavior->SetWait();
			return;
		}
	}

	controller->SetFocus(target);

	float distance = aiPawn->GetDistanceTo(target);

	if (distance < controller->GetBehaviorRange())
	{
		behavior->SetAvoid();
		return;
	}

	if (distance < controller->GetSightRadius())
	{
		behavior->SetAction();
		return;
	}
}
