#include "BTTaskNode_Change.h"
#include "Global.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"
#include "Components/CStateComponent.h"

UBTTaskNode_Change::UBTTaskNode_Change()
{
    NodeName = "Change";
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskNode_Change::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
    UCActionComponent* action = CHelpers::GetComponent<UCActionComponent>(controller->GetPawn());

    switch (Type)
    {
    case EActionType::Unarmed:
        break;
    case EActionType::Fist:
        break;
    case EActionType::OneHand:
        break;
    case EActionType::TwoHand:
        break;
    case EActionType::Warp:
        if(action->IsWarpHandMode() == false)
            action->SetWarpMode();
        break;
    case EActionType::MagicBall:
        if(action->IsMagicBallMode() == false)
        action->SetMagicBallMode();
        break;
    case EActionType::Storm:
        break;
    case EActionType::Max:
        break;
    }

    return EBTNodeResult::InProgress;
}

void UBTTaskNode_Change::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
    UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(controller->GetPawn());

    if (state->IsIdleMode())
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
