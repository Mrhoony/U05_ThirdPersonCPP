#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Warp.generated.h"

UCLASS()
class GAME_API ACDoAction_Warp : public ACDoAction
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

	virtual void Tick(float DeltaTime) override;

private:
	bool GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotator);

private:
	class UDecalComponent* Decal;
	class USkeletalMeshComponent* SkelMesh;
	class UStaticMeshComponent* StaticMesh;

	FVector Location;
};
