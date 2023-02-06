#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/TimelineComponent.h"
#include "CAim.generated.h"

UCLASS()
class GAME_API UCAim : public UObject
{
	GENERATED_BODY()

public:
	UCAim();
	
	void BeginPlay(class ACharacter* InOwnerCharacter);
	void Tick(float DeltaTime);

public:
	FORCEINLINE bool IsAvaliable() { return SpringArm != nullptr && Camera != nullptr; }

	void On();
	void Off();

private:
	UFUNCTION()
		void Zooming(float Output);

private:
	class ACharacter* OwnerCharacter;
	class USpringArmComponent* SpringArm; // CameraBoom�̶�� ����ǿ��� ���� �θ��µ�
	class UCameraComponent* Camera;

	bool bZooming;

	class UCurveFloat* Curve;
	FTimeline Timeline;
	FOnTimelineFloat TimelineFloat;
};
