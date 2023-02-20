#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CFootComponent.generated.h"

USTRUCT(BlueprintType)
struct FFootIKData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector LeftDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector RightDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector PelvisDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FRotator LeftRotation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FRotator RightRotation;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_API UCFootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCFootComponent();

public:
	FORCEINLINE const FFootIKData GetData() { return Data; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void Trace(FName InSocketName, float& OutDistance, FRotator& OutRotation);

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "IK")
		FName LeftFootSocket = "Foot_l";

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "IK")
		FName RightFootSocket = "Foot_r";

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "IK")
		float AdditionalDistance = 55.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "IK")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType = EDrawDebugTrace::ForDuration;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "IK")
		float OffsetDistance = 5.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "IK")
		float InterpSpeed = 20.f;

private:
	class ACharacter* OwnerCharacter;
	float CapsuleHalfHeight;
	FFootIKData Data;
};
