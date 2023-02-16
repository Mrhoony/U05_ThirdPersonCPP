#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_ActionItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActionItemSelected);

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

public:
	UPROPERTY(BlueprintAssignable)
		FActionItemSelected OnActionItemSelected;

private:
	class UCUserWidget_ActionContainer* GetActionContainer();
};
