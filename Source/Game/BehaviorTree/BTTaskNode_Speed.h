#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Components/CStatusComponent.h"
#include "BTTaskNode_Speed.generated.h"

UCLASS()
class GAME_API UBTTaskNode_Speed : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_Speed();

public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere)
		EMoveSpeedTypes MoveSpeedType;
};
