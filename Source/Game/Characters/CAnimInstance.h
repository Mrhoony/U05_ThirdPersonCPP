#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/CActionComponent.h"
#include "Components/CFootComponent.h"
#include "CAnimInstance.generated.h"

UCLASS()
class GAME_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EActionType ActionType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FFootIKData FootData;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bIKActive;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
		void OnActionTypeChanged(EActionType InPrevType, EActionType InNewType);
};
