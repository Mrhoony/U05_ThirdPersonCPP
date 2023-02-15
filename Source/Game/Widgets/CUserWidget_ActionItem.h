#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_ActionItem.generated.h"

UCLASS()
class GAME_API UCUserWidget_ActionItem : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
		void Pressed();

	UFUNCTION(BlueprintCallable)
		void Hover();

	UFUNCTION(BlueprintCallable)
		void Unhover();

private:
	class UCUserWidget_ActionContainer* GetActionContainer();
};
