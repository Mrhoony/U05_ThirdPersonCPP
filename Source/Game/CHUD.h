#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHUD.generated.h"

UCLASS()
class GAME_API ACHUD : public AHUD
{
	GENERATED_BODY()

public:
	ACHUD();

	virtual void DrawHUD() override;

	FORCEINLINE void VisibleAim() { bVisibleAim = true; }
	FORCEINLINE void HiddenAim() { bVisibleAim = false; }

private:
	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* Texture;

private:
	bool bVisibleAim;
};
