#include "BTTaskNode_Patrol.h"
#include "Global.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"
#include "Components/CPatrolComponent.h"

UBTTaskNode_Patrol::UBTTaskNode_Patrol()
{
    NodeName = "Patrol";
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    
    ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
    ACEnemy_AI* aiPawn = Cast<ACEnemy_AI>(controller->GetPawn());
    UCPatrolComponent* patrol = CHelpers::GetComponent<UCPatrolComponent>(aiPawn);

    FVector location;
    float acceptance;
    if (patrol->GetMoveTo(location, acceptance) == false)
    {
        return EBTNodeResult::Failed;
    }

    return EBTNodeResult::InProgress;
}

void UBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
    ACEnemy_AI* aiPawn = Cast<ACEnemy_AI>(controller->GetPawn());
    UCPatrolComponent* patrol = CHelpers::GetComponent<UCPatrolComponent>(aiPawn);

    FVector location;
    float acceptance;
    patrol->GetMoveTo(location, acceptance);

    EPathFollowingRequestResult::Type type = controller->MoveToLocation(location, acceptance, false);

    if (type == EPathFollowingRequestResult::Failed)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    if (type == EPathFollowingRequestResult::AlreadyAtGoal)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        patrol->UpdateNext();
    }
}
