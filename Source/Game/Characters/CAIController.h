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
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

public:
	float GetSightRadius();
	FORCEINLINE float GetBehaviorRange() { return BehaviorRange; }

private:
	UPROPERTY(VisibleDefaultsOnly) class UCBehaviorComponent* Behavior;
	UPROPERTY(VisibleDefaultsOnly) class UAIPerceptionComponent* Perception;	
	UPROPERTY(EditAnywhere) float BehaviorRange = 150.f;
	UPROPERTY(EditAnywhere) bool bDrawDebug = true;
	UPROPERTY(EditAnywhere) float InitHeight = 50.f;

private:
	class ACEnemy_AI* OwnerEnemy;
	class UAISenseConfig_Sight* Sight;
};
