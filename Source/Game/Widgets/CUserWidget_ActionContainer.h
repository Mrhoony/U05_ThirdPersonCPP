#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_ActionContainer.generated.h"

UCLASS()
class GAME_API UCUserWidget_ActionContainer : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE class UCUserWidget_ActionItem* GetItem(FString InName) { return Items[InName]; }

public:
	void Pressed(FString InName);
	void Hover(FString InName);
	void Unhover(FString InName);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UGridPanel* Grid;

	UPROPERTY(BlueprintReadOnly)
		TMap<FString, class UCUserWidget_ActionItem*> Items;
};
