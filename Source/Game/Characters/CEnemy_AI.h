#pragma once

#include "CoreMinimal.h"
#include "Characters/CEnemy.h"
#include "CEnemy_AI.generated.h"

UCLASS()
class GAME_API ACEnemy_AI : public ACEnemy
{
	GENERATED_BODY()

public:
	ACEnemy_AI();

public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;
};
