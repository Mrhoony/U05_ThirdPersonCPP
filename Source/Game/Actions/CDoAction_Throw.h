#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Throw.generated.h"

UCLASS()
class GAME_API ACDoAction_Throw : public ACDoAction
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

	virtual void Tick(float DeltaTime) override;

public:
	virtual void OnAim() override;
	virtual void OffAim() override;

private:
	UPROPERTY()
		class UCAim* Aim;
};
