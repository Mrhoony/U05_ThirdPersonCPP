#include "CUserWidget_ActionItem.h"
#include "Global.h"
#include "Widgets/CUserWidget_ActionContainer.h"
#include "Characters/CPlayer.h"

void UCUserWidget_ActionItem::Pressed()
{
	GetActionContainer()->Pressed(GetName());
}

void UCUserWidget_ActionItem::Hover()
{
	GetActionContainer()->Hover(GetName());
}

void UCUserWidget_ActionItem::Unhover()
{
	GetActionContainer()->Unhover(GetName());
}

UCUserWidget_ActionContainer* UCUserWidget_ActionItem::GetActionContainer()
{
	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	CheckNullResult(player, nullptr);

	CLog::Log(player->GetActionContainerWidget() == nullptr ? "Null" : "Not");

	return player->GetActionContainerWidget();
}
