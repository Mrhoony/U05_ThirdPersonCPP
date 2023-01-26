#include "CMontagesComponent.h"
#include "Global.h"
#include "Gameframework/Character.h"

UCMontagesComponent::UCMontagesComponent()
{
}

void UCMontagesComponent::BeginPlay()
{
	Super::BeginPlay();

	CheckNull(DataTable);

	TArray<FMontageData*> datas;
	DataTable->GetAllRows<FMontageData>("", datas);

	for (int32 i = 0; i < (int32)EStateType::Max; i++)
	{
		for (FMontageData* data : datas)
		{
			if ((EStateType)i == data->Type)
			{
				Datas[i] = data;			
				continue;
			}
		}
	}
}

void UCMontagesComponent::PlayAnimMontage(EStateType InType)
{
	ACharacter* owner = Cast<ACharacter>(GetOwner());
	CheckNull(owner);

	const FMontageData* data = Datas[(int32)InType];
	if (data != nullptr)
	{
		if(data->AnimMontage != nullptr)
			owner->PlayAnimMontage(data->AnimMontage, data->PlayRate, data->StartSection);
	}	
}
