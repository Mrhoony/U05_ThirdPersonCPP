#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "CDissolveComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAME_API UCDissolveComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCDissolveComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Play();
	void Stop();

private:
	UFUNCTION()
		void OnStartTimeline(float Output);

private:
	UPROPERTY(EditDefaultsOnly)
		class UMaterialInstanceConstant* Material;

	UPROPERTY(EditDefaultsOnly)
		class UCurveFloat* Curve;

	UPROPERTY(EditAnywhere)
		float PlayRate = 0.2f;

private:
	UPROPERTY()
		class UMaterialInstanceDynamic* DynamicMaterial;

	FTimeline Timeline;	
};
