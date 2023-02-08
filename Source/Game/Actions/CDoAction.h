#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CActionData.h"
#include "CDoAction.generated.h"

UCLASS()
class GAME_API ACDoAction : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDoAction();

	FORCEINLINE void SetDatas(TArray<FDoActionData> InDatas) { Datas = InDatas; }
	FORCEINLINE void SetEquipped(const bool* InEquipped) { bEquipped = InEquipped; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void DoAction() {};
	virtual void Begin_DoAction() {};
	virtual void End_DoAction() {};
	
	virtual void OnAim() {};
	virtual void OffAim() {};

	UFUNCTION()	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* Causer, class ACharacter* InOtherCharacter) {};
	UFUNCTION()	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* Causer, class ACharacter* InOtherCharacter) {};

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;

protected:
	TArray<FDoActionData> Datas;
	const bool* bEquipped;
};
