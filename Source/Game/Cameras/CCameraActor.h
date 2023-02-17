#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "CCameraActor.generated.h"

UCLASS()
class GAME_API ACCameraActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACCameraActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
		void OnBeginOverlap();

private:
	UFUNCTION()
		void OnPlay(float Output);

	UFUNCTION(BlueprintCallable)
		void OnFinish();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
		float PlayRate = 0.2f;

private:
	FTimeline Timeline;
	class ACCameraSpline* Spline;
};
