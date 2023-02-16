#include "CUserWidget_ActionContainer.h"
#include "Global.h"

#include "CUserWidget_ActionItem.h"
#include "Components/Border.h"

#include "Components/GridPanel.h"

void UCUserWidget_ActionContainer::NativeConstruct()
{
	TArray<UWidget*> children = Grid->GetAllChildren();

	for (UWidget* child : children)
	{
		Items.Add(child->GetName(), Cast<UCUserWidget_ActionItem>(child));
	}

	Super::NativeConstruct();
}

void UCUserWidget_ActionContainer::Pressed(FString InName)
{
	if (Items[InName]->OnActionItemSelected.IsBound())
		Items[InName]->OnActionItemSelected.Broadcast();

	SetVisibility(ESlateVisibility::Hidden);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}

void UCUserWidget_ActionContainer::Hover(FString InName)
{
	UBorder* border = Cast<UBorder>(Items[InName]->GetWidgetFromName("ItemBorder"));
	if (border != nullptr)
	{
		border->SetBrushColor(FLinearColor::Red);
	}
}

void UCUserWidget_ActionContainer::Unhover(FString InName)
{
	UBorder* border = Cast<UBorder>(Items[InName]->GetWidgetFromName("ItemBorder"));
	if (border != nullptr)
	{
		border->SetBrushColor(FLinearColor::White);
	}
}
