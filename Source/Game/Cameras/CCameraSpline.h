#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCameraSpline.generated.h"

UCLASS()
class GAME_API ACCameraSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	ACCameraSpline();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE class USplineComponent* GetSpline() { return Spline; }
	FORCEINLINE class UCurveFloat* GetCurve() { return Curve; }

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USplineComponent* Spline;

	UPROPERTY(EditDefaultsOnly)
		class UCurveFloat* Curve;
};
