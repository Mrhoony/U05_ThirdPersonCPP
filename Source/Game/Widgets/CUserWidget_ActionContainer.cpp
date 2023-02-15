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

}

void UCUserWidget_ActionContainer::Hover(FString InName)
{
	//CLog::Print(Items.Num());
	//for (auto item : Items)
	//{
	//	CLog::Print(item.Key);
	//	CLog::Print(item.Value == nullptr ? "Null" : "Not Null");
	//}

	/*UBorder* border = Cast<UBorder>(Items[InName]->GetWidgetFromName("ItemBorder"));
	if (border != nullptr)
	{
		border->SetBrushColor(FLinearColor::White);
	}*/
}

void UCUserWidget_ActionContainer::Unhover(FString InName)
{
	//UBorder* border = Cast<UBorder>(Items[InName]->GetWidgetFromName("ItemBorder"));
	//if (border != nullptr)
	//{
	//	border->SetBrushColor(FLinearColor::Red);
	//}
}
