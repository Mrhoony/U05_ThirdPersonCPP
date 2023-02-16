#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CDissolveComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_API UCDissolveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCDissolveComponent();

protected:
	virtual void BeginPlay() override;
};
