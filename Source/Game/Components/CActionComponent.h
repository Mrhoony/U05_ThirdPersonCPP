#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unarmed, Fist, OneHand, TwoHand, Warp, MagicBall, Storm, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChanged, EActionType, InPrevType, EActionType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCActionComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCActionObject* GetCurrent() { return DataObjects[(int32)Type]; }

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnaremdMode() { return Type == EActionType::Unarmed; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsFistMode() { return Type == EActionType::Fist; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsOneHandMode() { return Type == EActionType::OneHand; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsTwoHandMode() { return Type == EActionType::TwoHand; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsWarpHandMode() { return Type == EActionType::Warp; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsMagicBallMode() { return Type == EActionType::MagicBall; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsStormBallMode() { return Type == EActionType::Storm; }

public:
	UFUNCTION(BlueprintCallable) void SetUnaremdMode();
	UFUNCTION(BlueprintCallable) void SetFistMode();
	UFUNCTION(BlueprintCallable) void SetOneHandMode();
	UFUNCTION(BlueprintCallable) void SetTwoHandMode();
	UFUNCTION(BlueprintCallable) void SetWarpMode();
	UFUNCTION(BlueprintCallable) void SetMagicBallMode();
	UFUNCTION(BlueprintCallable) void SetStormMode();

	void DoAction();
	void DoOnAim();
	void DoOffAim();
	void Dead();
	void End_Dead();
	void OffAllCollisions();

public:
	UPROPERTY(BlueprintAssignable)
		FActionTypeChanged OnActionTypeChanged;

private:
	void SetMode(EActionType InNewType);
	void ChangeType(EActionType InNewType);

private:
	UPROPERTY(EditDefaultsOnly)
		class UCActionData* Datas[(int32)EActionType::Max]; // DataAsset (to Spawn)

	UPROPERTY()
		class UCActionObject* DataObjects[(int32)EActionType::Max]; // Spawned Objects

private:
	EActionType Type;
};
