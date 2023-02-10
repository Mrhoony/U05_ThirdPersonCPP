#include "BTTaskNode_Speed.h"
#include "Global.h"

#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"

UBTTaskNode_Speed::UBTTaskNode_Speed()
{
	NodeName = "Speed";
}

EBTNodeResult::Type UBTTaskNode_Speed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());

	ACEnemy_AI* aiPawn = Cast<ACEnemy_AI>(controller->GetPawn());
	UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(aiPawn);
	
	status->SetSpeed(MoveSpeedType);

	return EBTNodeResult::Succeeded;
}
