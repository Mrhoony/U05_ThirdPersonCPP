#include "CActionData.h"
#include "Global.h"
#include "CEquipment.h"
#include "CAttachment.h"
#include "CDoAction.h"
#include "GameFramework/Character.h"

void UCActionData::BeginPlay(ACharacter* InOnwerCharacter, UCActionObject** OutObject)
{
	FTransform transform;

	ACAttachment* Attachment = nullptr;

	if (AttachmentClass != nullptr)
	{
		Attachment = InOnwerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, transform, InOnwerCharacter);
		Attachment->SetActorLabel(GetLabelName(InOnwerCharacter, "Attachment"));
		UGameplayStatics::FinishSpawningActor(Attachment, transform);
	}
	
	ACEquipment* Equipment = nullptr;

	if (EquipmentClass != nullptr)
	{
		Equipment = InOnwerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass, transform, InOnwerCharacter);
		Equipment->AttachToComponent(InOnwerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		Equipment->SetData(EquipmentData);
		Equipment->SetColor(EquipmentColor);
		Equipment->SetActorLabel(GetLabelName(InOnwerCharacter, "Equipment"));
		UGameplayStatics::FinishSpawningActor(Equipment, transform);

		if (Attachment != nullptr)
		{
			Equipment->OnEquipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnEquip);
			Equipment->OnUnequipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnUnequip);
		}
	}

	ACDoAction* DoAction = nullptr;

	if (DoActionClass != nullptr)
	{
		DoAction = InOnwerCharacter->GetWorld()->SpawnActorDeferred<ACDoAction>(DoActionClass, transform, InOnwerCharacter);
		DoAction->AttachToComponent(InOnwerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		DoAction->SetDatas(DoActionDatas);
		DoAction->SetActorLabel(GetLabelName(InOnwerCharacter, "DoAction"));
		UGameplayStatics::FinishSpawningActor(DoAction, transform);

		if (Attachment != nullptr)
		{
			Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction, &ACDoAction::OnAttachmentBeginOverlap);
			Attachment->OnAttachmentEndOverlap.AddDynamic(DoAction, &ACDoAction::OnAttachmentEndOverlap);
		}

		if (Equipment != nullptr)
		{
			DoAction->SetEquipped(Equipment->IsEquipped());
		}
	}

	*OutObject = NewObject<UCActionObject>();
	(*OutObject)->Attachment = Attachment;
	(*OutObject)->Equipment = Equipment;
	(*OutObject)->DoAction = DoAction;
	(*OutObject)->EquipmentColor = EquipmentColor;
}

FString UCActionData::GetLabelName(ACharacter* InOnwerCharacter, FString InMiddleName)
{
	FString name;
	name.Append(InOnwerCharacter->GetActorLabel());
	name.Append("_");
	name.Append(InMiddleName);
	name.Append("_");
	name.Append(GetName().Replace(L"DA_", L""));

	return name;
}
