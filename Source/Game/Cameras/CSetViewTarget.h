#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSetViewTarget.generated.h"

UCLASS()
class GAME_API ACSetViewTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSetViewTarget();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void Change();

private:
	UPROPERTY(EditInstanceOnly)
	TArray<class ACameraActor*> Cameras;

	UPROPERTY(EditInstanceOnly)
	bool bActivation;

private:
	uint32 Index;
};
