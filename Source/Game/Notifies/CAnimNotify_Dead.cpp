#include "CAnimNotify_Dead.h"
#include "Global.h"
#include "Characters/ICharacter.h"

FString UCAnimNotify_Dead::GetNotifyName_Implementation() const
{
	return "Dead";
}
void UCAnimNotify_Dead::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	IICharacter* characterInterface = Cast<IICharacter>(MeshComp->GetOwner());
	CheckNull(characterInterface);

	characterInterface->End_Dead();
}
