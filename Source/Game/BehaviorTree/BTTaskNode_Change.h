#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Components/CActionComponent.h"
#include "BTTaskNode_Change.generated.h"

UCLASS()
class GAME_API UBTTaskNode_Change : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_Change();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere)
		EActionType Type;
};
