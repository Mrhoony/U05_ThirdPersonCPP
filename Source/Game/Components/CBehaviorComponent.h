#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait, Approach, Action, Patrol, Hitted, Avoid
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBehaviorTypeChanged, EBehaviorType, InPrevType, EBehaviorType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_API UCBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCBehaviorComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)		bool IsWait(); // { return GetType() == EBehaviorType::Wait; }
	UFUNCTION(BlueprintPure)		bool IsApproach();
	UFUNCTION(BlueprintPure)		bool IsAction();
	UFUNCTION(BlueprintPure)		bool IsPatrol();
	UFUNCTION(BlueprintPure)		bool IsHitted();
	UFUNCTION(BlueprintPure)		bool IsAvoid();

public:
	void SetWait();
	void SetApproach();
	void SetAction();
	void SetPatrol();
	void SetHitted();
	void SetAvoid();

	FORCEINLINE void SetBlackboard(class UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }

	class ACPlayer* GetTargetPlayer();
	FVector GetWarpLocation();

private:
	void ChangeType(EBehaviorType InType);
	EBehaviorType GetType();

public:
	UPROPERTY(BlueprintAssignable)
		FBehaviorTypeChanged OnBehaviorTypeChanged;

private:
	UPROPERTY(EditAnywhere)
		FName BehaviorKey = "Behavior";

	UPROPERTY(EditAnywhere)
		FName PlayerKey = "Player";

	UPROPERTY(EditAnywhere)
		FName WarpLocationKey = "WarpLocation";

private:
	class UBlackboardComponent* Blackboard;	
};
