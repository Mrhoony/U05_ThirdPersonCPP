#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"

UENUM(BlueprintType)
enum class EMoveSpeedTypes : uint8
{
	Sneak, Walk, Run, Max
};

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
	FORCEINLINE float GetSneakSpeed() { return Speed[(int32)EMoveSpeedTypes::Sneak]; }
	FORCEINLINE float GetWalkSpeed() { return Speed[(int32)EMoveSpeedTypes::Walk]; }
	FORCEINLINE float GetRunSpeed() { return Speed[(int32)EMoveSpeedTypes::Run]; }
	FORCEINLINE bool IsCanMove() { return bCanMove; }

	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE float GetHealth() { return Health; }

	void SetMove();
	void SetStop();

	void SetSpeed(EMoveSpeedTypes InType);

private:		
	UPROPERTY(EditAnywhere, Category = "Speed")
		float Speed[(int32)EMoveSpeedTypes::Max] = { 200, 400, 600 };

	UPROPERTY(EditAnywhere, Category = "Health")
		float MaxHealth = 100;		

private:
	bool bCanMove = true;
	float Health;
};
