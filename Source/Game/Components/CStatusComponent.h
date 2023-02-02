#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStatusComponent();

	void IncreaseHealth(float InAmount);
	void DecreaseHealth(float InAmount);

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE float GetSneakSpeed() { return SneakSpeed; }
	FORCEINLINE float GetWalkSpeed() { return WalkSpeed; }
	FORCEINLINE float GetRunSpeed() { return RunSpeed; }
	FORCEINLINE bool IsCanMove() { return bCanMove; }

	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE float GetHealth() { return Health; }

	void SetMove();
	void SetStop();

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
		float SneakSpeed = 200;

	UPROPERTY(EditAnywhere, Category = "Speed")
		float WalkSpeed = 400;
		
	UPROPERTY(EditAnywhere, Category = "Speed")
		float RunSpeed = 600;

	UPROPERTY(EditAnywhere, Category = "Health")
		float MaxHealth = 100;		

private:
	bool bCanMove = true;
	float Health;
};
