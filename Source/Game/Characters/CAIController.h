#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

UCLASS()
class GAME_API ACAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ACAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnUnPossess() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCBehaviorComponent* Behavior;

	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* Perception;

private:
	class ACEnemy_AI* OwnerEnemy;

private:
	class UAISenseConfig_Sight* Sight;
};
